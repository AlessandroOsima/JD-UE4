// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCController/BHT/Decorators/BTDecorator_BaseStateCheck.h"
#include "BTDecorator_DeadState.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTDecorator_DeadState : public UBTDecorator_BaseStateCheck
{
	GENERATED_UCLASS_BODY()

    
    virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent * _ownerComp) const override;
	
};
