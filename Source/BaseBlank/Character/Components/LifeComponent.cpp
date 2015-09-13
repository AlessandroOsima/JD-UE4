// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "LifeComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Components/LifeComponent.h"
#include "Character/Configuration/CharacterConfigurationAsset.h"

ULifeComponent::ULifeComponent(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}


float ULifeComponent::GetLife() const
{
    return Life;
}

void ULifeComponent::SetLife(float _life)
{
	float oldLife = Life;

    Life = _life;
    
    if(Life < 0)
    {
        Life = 0;
    }
    else if(Life > GetMaxLife())
    {
        Life = GetMaxLife();
    }

	LifeChange.Broadcast(m_owner, oldLife, Life);

}

void ULifeComponent::ApplyDamage(float _damage)
{
	float oldLife = Life;

    Life -= _damage;
    
    if(Life < 0)
    {
        Life = 0;
    }
    else if(Life > GetMaxLife())
    {
        Life = GetMaxLife();
    }

	LifeChange.Broadcast(m_owner, oldLife, Life);
}

void ULifeComponent::Kill()
{
	float OldLife = Life;

	Life = 0;

	LifeChange.Broadcast(m_owner, OldLife, Life);
}

float ULifeComponent::GetMaxLife() const
{
    return m_ownerConfiguration->MaxLife;
}

void ULifeComponent::HealToFull()
{
	float OldLife = Life;

    Life = GetMaxLife();

	LifeChange.Broadcast(m_owner, OldLife, Life);

}

void ULifeComponent::BeginPlay()
{
    Super::BeginPlay();
    
    Life = GetMaxLife();
    
	m_ownerBlackboard->RegisterObserver(m_ownerBlackboard->GetKeyID(m_owner->GetBlackboardKeys().DamageInfo), this, FOnBlackboardChangeNotification::CreateUObject(this, &ULifeComponent::OnApplyDamage));
}

EBlackboardNotificationResult ULifeComponent::OnApplyDamage(const class UBlackboardComponent & _blk, FBlackboard::FKey _key)
{
    if(_key == m_ownerBlackboard->GetKeyID(m_owner->GetBlackboardKeys().DamageInfo))
    {
        UDamageInfo * damageInfo = Cast<UDamageInfo>(m_ownerBlackboard->GetValueAsObject(m_owner->GetBlackboardKeys().DamageInfo));
        
        if(damageInfo)
        {
            ApplyDamage(damageInfo->DamageAmount);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[ULifeComponent]Received wrong blk entry"))
    }

	return EBlackboardNotificationResult::ContinueObserving;
}

void ULifeComponent::OnOwnerConfigurationChange()
{
    if(m_ownerConfiguration->HealToMaxLifeOnConfigChange)
    {
        HealToFull();
    }
}