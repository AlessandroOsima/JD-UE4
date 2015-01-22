// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FreeModeSoulsInfoComponent.generated.h"


class UFreeGameModeConfigurationAsset;

/**
 * 
 */
UCLASS()
class BASEBLANK_API UFreeModeSoulsInfoComponent : public UActorComponent
{
	GENERATED_BODY()

private:
    UFreeGameModeConfigurationAsset * m_ownerConfig;
    
    int32 m_currentSouls;
    
public:
    
    UFUNCTION(BlueprintCallable, Category="JD,Souls Management")
    void SetGameModeInfoConfig(UFreeGameModeConfigurationAsset * _config);
    
    UFUNCTION(BlueprintCallable, Category="JD,Souls Management")
    void SetSoulsAmount(int32 _soulsAmount);
    
    UFUNCTION(BlueprintCallable, Category="JD,Souls Management")
    int32 GetSoulsAmount() const;
    
    UFUNCTION(BlueprintCallable, Category="JD,Souls Management")
    int32 UseSoulsAmount(int32 _amount);
    
    UFUNCTION(BlueprintCallable, Category="JD,Souls Management")
    bool CanSpendSouls(int32 _amountToSpend) const;
};
