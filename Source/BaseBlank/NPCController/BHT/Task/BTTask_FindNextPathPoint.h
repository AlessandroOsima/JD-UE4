// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNextPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTask_FindNextPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
    
    UBTTask_FindNextPathPoint(const class FObjectInitializer& PCIP);
	
    UPROPERTY(EditAnywhere, Category=Node)
    bool Loop;
    
    virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
    virtual void DescribeRuntimeValues(const class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
    virtual FString GetStaticDescription() const override;
    
    int32 GetCurrentPathIndex(const class UBehaviorTreeComponent& OwnerComp) const;
};
