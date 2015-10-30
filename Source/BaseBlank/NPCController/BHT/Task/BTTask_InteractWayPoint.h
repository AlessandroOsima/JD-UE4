

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Waypoints/WaypointInteractionComponent.h"
#include "BTTask_InteractWayPoint.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTask_InteractWayPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBehaviorTreeComponent * MyOwnerComp;

	UBTTask_InteractWayPoint(const class FObjectInitializer& PCIP);

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void DescribeRuntimeValues(const class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	void OnInteractionWithWaypointOver(UWaypointInteractionComponent * InteractionComponent, APawn * Target);

	FDelegateHandle OnWaypointInteractionHandle;
};
