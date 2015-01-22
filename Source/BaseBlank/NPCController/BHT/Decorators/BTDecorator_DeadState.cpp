// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTDecorator_DeadState.h"
#include "Character/BaseCharacter.h"
#include "NPCController/Components/BehaviourComponent.h"

UBTDecorator_DeadState::UBTDecorator_DeadState(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    NodeName = "Dead";
}


bool UBTDecorator_DeadState::CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent * _ownerComp) const
{
    bool canEnter = false;
    
    if(GetBehaviourComponent(_ownerComp)->GetNPCBehaviour()  == ENPCBehaviour::Dead)
    {
        canEnter = true;
    }
    
    return canEnter;
}