// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BehaviourComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Components/LifeComponent.h"



void UBehaviourComponent::SetTargetNPC(ABaseCharacter * _targetNPC)
{
    check(_targetNPC)
    
    m_targetNPC = _targetNPC;
}

ENPCBehaviour UBehaviourComponent::GetNPCBehaviour()
{
    ENPCBehaviour bh = ENPCBehaviour::Normal;
    
    if(m_targetNPC != nullptr)
    {
        ULifeComponent * life = Cast<ULifeComponent>(m_targetNPC->GetComponentByClass(ULifeComponent::StaticClass()));
        
        if(life != nullptr)
        {
            if(life->GetLife() > 0)
            {
                if(life->GetLife() > life->GetMaxLife()/2)
                {
                    bh = ENPCBehaviour::Normal;
                }
                else
                {
                    bh = ENPCBehaviour::Injured;
                }
            }
            else
            {
                bh = ENPCBehaviour::Dead;
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[UBehaviourComponent]No life component found"))
        }
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[UBehaviourComponent]Target NPC is null"))
    }
    
    return bh;
}