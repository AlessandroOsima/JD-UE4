// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCController/BHT/Decorators/BTDecorator_BaseStateCheck.h"
#include "BTDecorator_InjuredStateCheck.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTDecorator_InjuredStateCheck : public UBTDecorator_BaseStateCheck
{
	GENERATED_BODY()

public:
	
    UBTDecorator_InjuredStateCheck(const class FObjectInitializer& PCIP);

protected:
	virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent * _ownerComp) const override;
	
};
