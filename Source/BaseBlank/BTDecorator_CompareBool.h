

#pragma once

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CompareBool.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTDecorator_CompareBool : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()


public:
	UBTDecorator_CompareBool(const class FObjectInitializer& PCIP);

	virtual bool CalculateRawConditionValue(class UBehaviorTreeComponent & _ownerComp, uint8* _nodeMemory) const override;

	virtual FString GetStaticDescription() const override;


	
};
