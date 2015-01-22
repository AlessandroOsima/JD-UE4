// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Components/BaseCharacterComponent.h"
#include "PathPointsComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UPathPointsComponent : public UBaseCharacterComponent
{
	GENERATED_UCLASS_BODY()

    TArray<AActor *> SpawnPoints;
    
public:
    
    UFUNCTION(BlueprintCallable, Category="JD,Path Points")
    void SetPathPoints(TArray<AActor *> _spawnPoints);
    
    UFUNCTION(BlueprintCallable, Category="JD,Path Points")
    TArray<AActor *> GetPathPoints();
    
};
