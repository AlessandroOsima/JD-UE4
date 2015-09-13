#pragma once

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTTDecorator_IsCurrentMoveTarget.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTDecorator_IsCurrentMoveTarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTDecorator_IsCurrentMoveTarget(const class FObjectInitializer& PCIP);

	virtual bool CalculateRawConditionValue(class UBehaviorTreeComponent & _ownerComp, uint8* _nodeMemory) const override;

	virtual FString GetStaticDescription() const override;

	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

};
