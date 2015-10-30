// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "FreeGameModeConfigurationAsset.h"
#include "FreeModeSoulsInfoComponent.h"



void UFreeModeSoulsInfoComponent::SetGameModeInfoConfig(UFreeGameModeConfigurationAsset *_config)
{
	ensureMsgf(_config != nullptr, TEXT("[UFreeModeSoulsInfoComponent]Trying to set a NULL config"));
    
    
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
	float oldCurrent = m_currentSouls;

    m_currentSouls = _soulsAmount;

	SoulsChangeEvent.Broadcast(oldCurrent, m_currentSouls);
}

int32 UFreeModeSoulsInfoComponent::GetSoulsAmount() const
{
    return m_currentSouls;
}

int32 UFreeModeSoulsInfoComponent::UseSoulsAmount(int32 _amount)
{
	float oldCurrent = m_currentSouls;

    m_currentSouls -= _amount;

	if (m_currentSouls < 0)
	{
		m_currentSouls = 0;
	}

	SoulsChangeEvent.Broadcast(oldCurrent, m_currentSouls);
    
    return m_currentSouls;
}