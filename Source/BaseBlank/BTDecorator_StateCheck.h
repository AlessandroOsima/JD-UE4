// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCController/BHT/Decorators/BTDecorator_BaseStateCheck.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "BTDecorator_StateCheck.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTDecorator_StateCheck : public UBTDecorator_BaseStateCheck
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere)
    ENPCBehaviour BehaviourToEnter;
    
public:
    UBTDecorator_StateCheck(const class FObjectInitializer& PCIP);
    
protected:
    virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent & _ownerComp) const override;
	virtual FString GetStaticDescription() const override;
	
};
