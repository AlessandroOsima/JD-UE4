// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTDecorator_InjuredStateCheck.h"
#include "NPCController/Components/BehaviourComponent.h"

bool UBTDecorator_InjuredStateCheck::CanEnterInState(ABaseCharacter *_target, class UBehaviorTreeComponent *_ownerComp) const
{
    bool canEnter = false;
    UBehaviourComponent * cmp = GetBehaviourComponent(_ownerComp);
    
    if(cmp->GetNPCBehaviour() == ENPCBehaviour::Injured)
    {
        canEnter = true;
    }
    
    return canEnter;
}

UBTDecorator_InjuredStateCheck::UBTDecorator_InjuredStateCheck(const class FObjectInitializer& PCIP)
: Super(PCIP)
{
    NodeName = "Injured";
}

