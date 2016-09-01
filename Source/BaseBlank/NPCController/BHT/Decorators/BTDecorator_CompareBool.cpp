

#include "BaseBlank.h"
#include "BTDecorator_CompareBool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"





UBTDecorator_CompareBool::UBTDecorator_CompareBool(const class FObjectInitializer& PCIP)
{
	NodeName = "Check Blackboard Boolean Values";
	//BlackboardKey.AddObjectFilter(this, ANPCController::StaticClass());
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CompareBool, BlackboardKey));
}

bool UBTDecorator_CompareBool::CalculateRawConditionValue(class UBehaviorTreeComponent & _ownerComp, uint8* _nodeMemory) const
{
	bool res = _ownerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(BlackboardKey.GetSelectedKeyID());
	return res;

}

FString UBTDecorator_CompareBool::GetStaticDescription() const
{
	return FString::Printf(TEXT("If a bool Blackboard value is true or false"));
}
