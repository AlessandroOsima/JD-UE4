// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCController/BHT/Decorators/BTDecorator_BaseStateCheck.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "BTDecorator_StateCheck.generated.h"

class ANPCController;

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
	void OnBehaviourChanged(ABaseCharacter * Character, ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior);

protected:
    virtual bool CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent & _ownerComp) const override;
	virtual FString GetStaticDescription() const override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);	
};
