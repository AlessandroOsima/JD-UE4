// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SelectMoveTarget.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTask_SelectMoveTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
    UBTTask_SelectMoveTarget(const class FObjectInitializer& PCIP);
    
    virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;
    
    UPROPERTY(EditAnywhere, Category=Blackboard)
    FBlackboardKeySelector TargetLocation;
    
    UPROPERTY(EditAnywhere, Category=Blackboard)
    FBlackboardKeySelector TargetObject;
    
    UPROPERTY(EditAnywhere, Category=Blackboard)
    FBlackboardKeySelector TargetIndex;
    
    virtual FString GetStaticDescription() const override;
    
    virtual void InitializeFromAsset(class UBehaviorTree & _asset) override;
    
private:
    
    int32 GetCurrentPathIndex(const class UBehaviorTreeComponent * OwnerComp) const;

    
};
