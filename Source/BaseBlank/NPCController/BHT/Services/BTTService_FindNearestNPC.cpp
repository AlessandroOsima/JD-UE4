#include "BaseBlank.h"
#include "Global/BaseBlankGameMode.h"
#include "NPCController/NPCController.h"
#include <limits>
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BTTService_FindNearestNPC.h"
#include "Character/Effects/ZombieEffect.h"
#include "Character/BaseCharacter.h"
#include "AI/NavigationSystemHelpers.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(NPCBHT);


UBTTService_FindNearestNPC::UBTTService_FindNearestNPC(const class FObjectInitializer& PCIP) : Super(PCIP), ExcludeAllEffects(false)
{
	NodeName = "Find Nearest NPC";
	BlackboardKey.AddObjectFilter(this, ANPCController::StaticClass());
	BlackboardKeyPosition.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTService_FindNearestNPC, BlackboardKeyPosition));
	BlackboardKeyFoundNPCS.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTService_FindNearestNPC, BlackboardKeyFoundNPCS));
}

void UBTTService_FindNearestNPC::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	BlackboardKeyPosition.CacheSelectedKey(GetBlackboardAsset());
	BlackboardKeyFoundNPCS.CacheSelectedKey(GetBlackboardAsset());

}

FString UBTTService_FindNearestNPC::GetStaticServiceDescription() const
{
	return TEXT("Search for the nearest npc");
}

void UBTTService_FindNearestNPC::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABaseBlankGameMode * gameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());

	ensure(gameMode);

	TArray<ANPCController *>& npcs = gameMode->GetNPCs();

	ANPCController * controller = nullptr;
	float distance = std::numeric_limits<float>::max();

	FVector ownerLocation = OwnerComp.GetOwner()->GetActorLocation();

	for (auto npc : npcs)
	{
		bool hasEffects = false;

		if (!ExcludeAllEffects)
		{
			for (int i = 0; i < npc->GetBaseCharacter()->PowerInteractionsComponent->Effects.Num(); i++)
			{
				for (int x = 0; x < ExcludeEffects.Num(); x++)
				{
					if (npc->GetBaseCharacter()->PowerInteractionsComponent->HasEffectOfClass(UZombieEffect::StaticClass(), false, true))
					{
						hasEffects = true;
						break;
					}
				}
			}
		}
		else if (npc->GetBaseCharacter()->PowerInteractionsComponent->Effects.Num() != 0)
		{
			hasEffects = true;
		}

		if (npc && npc != OwnerComp.GetOwner() && npc->BehaviourComponent->GetNPCBehaviour() != ENPCBehaviour::Dead && !hasEffects)
		{
			float localDistance = FVector::DistSquared(ownerLocation, npc->GetPawn()->GetActorLocation());

			if (localDistance < distance)
			{
				distance = localDistance;
				controller = npc;
			}
		}
	}

	 //If the pawn is a base character the do checks and filter based on effect
	if (controller == nullptr)
	{
		bool val = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(BlackboardKeyFoundNPCS.GetSelectedKeyID());
		if (OwnerComp.GetAIOwner()->GetPathFollowingComponent()->HasValidPath() && val)
		{
			OwnerComp.GetAIOwner()->GetPathFollowingComponent()->AbortMove(TEXT("[FindNearest]Moving to Random Path"));
		}

		UNavigationSystem * navSystem = UNavigationSystem::GetCurrent(GetWorld());

		FNavLocation location{};
		if (navSystem->GetRandomReachablePointInRadius(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), SearchRadius, location))
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), nullptr);
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKeyPosition.GetSelectedKeyID(), location.Location);
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(BlackboardKeyFoundNPCS.GetSelectedKeyID(), false);

			UE_VLOG_SEGMENT(OwnerComp.GetOwner(), NPCBHT, Log, OwnerComp.GetOwner()->GetActorLocation() + FVector(0, 0, 30), location.Location + FVector(0, 0, 30), FColor::Red, TEXT("NPC Not Found Path"));
			UE_VLOG_BOX(OwnerComp.GetOwner(), NPCBHT, Log, FBox(location.Location - FVector(30.0f), location.Location + FVector(30.0f)), FColor::Red, TEXT("NPC Not Found Random Position"));
		
		}

		return;
	}

	FVector location = controller->GetControlledPawn()->GetActorLocation();

	UE_VLOG_SEGMENT(OwnerComp.GetOwner(), NPCBHT, Log, OwnerComp.GetAIOwner()->GetControlledPawn()->GetActorLocation() + FVector(0, 0, 30), location + FVector(0, 0, 30), FColor::Green, TEXT("NPC Target"));
	UE_VLOG_BOX(OwnerComp.GetOwner(), NPCBHT, Log, FBox(location - FVector(30.0f), location + FVector(30.0f)),FColor::Green, TEXT("NPC Target Position"));

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKeyPosition.GetSelectedKeyID(), location);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(BlackboardKeyFoundNPCS.GetSelectedKeyID(), true);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), controller);
}
