#include "BaseBlank.h"
#include "Global/BaseBlankGameMode.h"
#include "NPCController/NPCController.h"
#include <limits>
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BTTService_FindNearestNPC.h"
#include "Character/BaseCharacter.h"



UBTTService_FindNearestNPC::UBTTService_FindNearestNPC(const class FObjectInitializer& PCIP) : Super(PCIP), ApplyWithEffects(false)
{
	NodeName = "Find Nearest NPC";
	BlackboardKey.AddObjectFilter(this, ANPCController::StaticClass());
}

void UBTTService_FindNearestNPC::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
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

	bool hasEffects = false;

	for (auto npc : npcs)
	{
		hasEffects = ApplyWithEffects ? true : npc->GetBaseCharacter()->PowerInteractionsComponent->Effects.Num() == 0;

		if (npc && npc != OwnerComp.GetOwner() && npc->BehaviourComponent->GetNPCBehaviour() != ENPCBehaviour::Dead && hasEffects)
		{
			float localDistance = FVector::DistSquared(ownerLocation, npc->GetPawn()->GetActorLocation());

			if (localDistance < distance)
			{
				distance = localDistance;
				controller = npc;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), controller);
}
