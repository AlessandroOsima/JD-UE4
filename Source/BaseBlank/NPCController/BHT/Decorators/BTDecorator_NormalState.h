// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCController/BHT/Decorators/BTDecorator_BaseStateCheck.h"
#include "BTDecorator_NormalState.generated.h"

/**
 * 
 */
class ULifeComponent;

UCLASS()
class BASEBLANK_API UBTDecorator_NormalState : public UBTDecorator_BaseStateCheck
{
	GENERATED_UCLASS_BODY()
    
    
    virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent * _ownerComp) const override;
    virtual FString GetStaticDescription() const override;
    
};
