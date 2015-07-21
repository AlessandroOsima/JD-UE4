// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_BaseStateCheck.generated.h"

class ABaseCharacter;
class UBehaviourComponent;

/**
 *Common class for all the decorators that will do state checking on the Character BHT
 *Overload CanEnterInState to do state checking on _target
 */
UCLASS()
class BASEBLANK_API UBTDecorator_BaseStateCheck : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

protected:
    //The entry on the blackboard we have to check for state
    UPROPERTY(EditAnywhere, Category=Blackboard)
    FBlackboardKeySelector TargetNPC;
    
    UBehaviourComponent * GetBehaviourComponent(class UBehaviorTreeComponent & _ownerComp) const;
    
    //Cache TargetNPC
    virtual void InitializeFromAsset(class UBehaviorTree & _asset) override;
    //Overload to do state checking, _target is always non null
    virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent & _ownerComp) const;
    //Finds TargetNPC on the blackboard and does safety checks before calling CanEnterInState
    virtual bool CalculateRawConditionValue(class UBehaviorTreeComponent & _ownerComp, uint8* _nodeMemory) const override;
    
    //Overload to add state information on the BHT editor in UnrealEd
    virtual FString GetStaticDescription() const override;
    
#if WITH_EDITOR
    virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
    
};
