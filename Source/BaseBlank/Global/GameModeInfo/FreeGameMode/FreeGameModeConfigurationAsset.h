// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "FreeGameModeConfigurationAsset.generated.h"

USTRUCT()
struct FVictoryConditionsInfo
{
    GENERATED_USTRUCT_BODY()
    
public:
    
    UPROPERTY(EditAnywhere)
    int32 SoulsAmount;
    
    UPROPERTY(EditAnywhere)
    FString VictoryText;
};

/**
 * 
 */
UCLASS()
class BASEBLANK_API UFreeGameModeConfigurationAsset : public UDataAsset
{
	GENERATED_BODY()
    
public:

	UPROPERTY(EditAnywhere, Category="Level Start")
    int32 Souls;
    
    UPROPERTY(EditAnywhere, Category="End Game Conditions")
    TArray<FVictoryConditionsInfo> VictoriesCounditionSouls;
    
    UPROPERTY(EditAnywhere, Category="End Game Conditions")
    int32 LoseConditionSouls;
    
    
    //Powers Info here
};
