#include "BaseBlank.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Components/PathPointsComponent.h"
#include "Waypoints/WaypointInteractionComponent.h"
#include "AIController.h"
#include "Character/BaseCharacter.h"
#include "BTTask_InteractWayPoint.h"




UBTTask_InteractWayPoint::UBTTask_InteractWayPoint(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	NodeName = "Interact With Waypoint";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_InteractWayPoint::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	MyOwnerComp = &OwnerComp;

	AAIController * aiController = Cast<AAIController>(OwnerComp.GetOwner());

	ensure(aiController);
	ensure(OwnerComp.GetBlackboardComponent());

	int32 WaypointIndex = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(BlackboardKey.GetSelectedKeyID());

	APawn * target = aiController->GetPawn();

	ensure(target);

	ABaseCharacter * castedTarget = Cast<ABaseCharacter>(target);

	ensure(castedTarget);

	UPathPointsComponent * pathPointsCmp = Cast<UPathPointsComponent>(castedTarget->GetComponentByClass(UPathPointsComponent::StaticClass()));

	if (WaypointIndex >= 0 && WaypointIndex < pathPointsCmp->GetPathPoints().Num())
	{
		AActor * TargetWaypoint = pathPointsCmp->GetPathPoints()[WaypointIndex];
		
		UWaypointInteractionComponent * cmp = (UWaypointInteractionComponent *)TargetWaypoint->GetComponentByClass(UWaypointInteractionComponent::StaticClass());
		
		if (cmp)
		{
			//Apply action based on target type
			if (!cmp->IsInteractingWithTarget(target))
			{
				cmp->Interact(castedTarget);
				OnWaypointInteractionHandle = cmp->OnInteractionOver().AddUObject(this, &UBTTask_InteractWayPoint::OnInteractionWithWaypointOver);
				return EBTNodeResult::InProgress;
			}
		}
		else
		{
			//Should wait some time here, or fail to a wait node
			return EBTNodeResult::Succeeded;
		}

		
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[BTTask_InteractWayPoint]The path index is out of boundaries"))
	}


	return EBTNodeResult::Failed;
}

void UBTTask_InteractWayPoint::DescribeRuntimeValues(const class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

FString UBTTask_InteractWayPoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("Interact With Current Waypoint"));
}

void UBTTask_InteractWayPoint::OnInteractionWithWaypointOver(UWaypointInteractionComponent * InteractionComponent, APawn * Target)
{
	//Aka the controller
	AActor * OwnerCotroller = MyOwnerComp->GetOwner();
	AActor * TargetController = Target->GetController();

	if (MyOwnerComp && TargetController == OwnerCotroller)
	{
		FinishLatentTask(MyOwnerComp, EBTNodeResult::Succeeded);
		InteractionComponent->OnInteractionOver().Remove(OnWaypointInteractionHandle);
	}
}
