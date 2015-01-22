// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "FreeGameModeConfigurationAsset.h"
#include "FreeModeSoulsInfoComponent.h"



void UFreeModeSoulsInfoComponent::SetGameModeInfoConfig(UFreeGameModeConfigurationAsset *_config)
{
    ensureMsg(_config != nullptr, TEXT("[UFreeModeSoulsInfoComponent]Trying to set a NULL config"));
    
    
    m_ownerConfig = _config;
    
    m_currentSouls = m_ownerConfig->Souls;
    
}

bool UFreeModeSoulsInfoComponent::CanSpendSouls(int32 _amountToSpend) const
{
    if((m_currentSouls - _amountToSpend) > m_ownerConfig->LoseConditionSouls)
    {
        return true;
    }
    
    return false;
}


void UFreeModeSoulsInfoComponent::SetSoulsAmount(int32 _soulsAmount)
{
    m_currentSouls = _soulsAmount;
}

int32 UFreeModeSoulsInfoComponent::GetSoulsAmount() const
{
    return m_currentSouls;
}

int32 UFreeModeSoulsInfoComponent::UseSoulsAmount(int32 _amount)
{
    m_currentSouls += _amount;
    
    return m_currentSouls;
}