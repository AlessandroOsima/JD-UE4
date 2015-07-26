#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RemoveEffects.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTask_RemoveEffects : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_RemoveEffects(const class FObjectInitializer& PCIP);
	
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

};
