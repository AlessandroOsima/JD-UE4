// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTDecorator_NormalState.h"
#include "Character/BaseCharacter.h"
#include "NPCController/Components/BehaviourComponent.h"

UBTDecorator_NormalState::UBTDecorator_NormalState(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    NodeName = "Normal";
}


bool UBTDecorator_NormalState::CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent * _ownerComp) const
{

    bool canEnter = false;
    
    if(GetBehaviourComponent(_ownerComp)->GetNPCBehaviour() == ENPCBehaviour::Normal)
    {
        canEnter = true;
    }
    
    return canEnter;
    
}

FString UBTDecorator_NormalState::GetStaticDescription() const
{
    return FString::Printf(TEXT("%s"),*Super::GetStaticDescription());
}