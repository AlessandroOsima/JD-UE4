#include "BaseBlank.h"
#include "NPCController/NPCController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BTTDecorator_IsCurrentMoveTarget.h"


UBTTDecorator_IsCurrentMoveTarget::UBTTDecorator_IsCurrentMoveTarget(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	NodeName = "Is Current Move Target";
	BlackboardKey.AddObjectFilter(this, ANPCController::StaticClass());
}

bool UBTTDecorator_IsCurrentMoveTarget::CalculateRawConditionValue(class UBehaviorTreeComponent & _ownerComp, uint8* _nodeMemory) const
{
	AAIController * controller = _ownerComp.GetAIOwner();

	ensureMsg(controller, TEXT("No controller found, this decorator only works with an AI controller subclass"));

	bool result = false;

	AActor * goal  = controller->GetPathFollowingComponent()->GetMoveGoal();

	bool isPathFollowing = controller->GetPathFollowingComponent()->GetStatus() != EPathFollowingStatus::Idle;

	if (!isPathFollowing || isPathFollowing && goal == _ownerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()))
	{
		result = true;
	}

	return result;
}

FString UBTTDecorator_IsCurrentMoveTarget::GetStaticDescription() const
{
	return FString::Printf(TEXT("If the actor is moving toward blackboard target"));
}

void UBTTDecorator_IsCurrentMoveTarget::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp)
	{
		FString KeyValue = BlackboardComp->DescribeKeyValue(BlackboardKey.GetSelectedKeyID(), EBlackboardDescription::OnlyValue);
		Values.Add(FString::Printf(TEXT("Target Object is: %s"), *KeyValue));
	}

	
}

