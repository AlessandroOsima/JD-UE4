// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Character/BaseCharacter.h"
#include "SpawnPoint.generated.h"

class UCharacterConfigurationAsset;

/**
 * 
 */
UCLASS()
class BASEBLANK_API ASpawnPoint : public AActor
{
	GENERATED_UCLASS_BODY()

    FRotator  m_rotator;
    FVector m_position;
    
public:
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Configuration)
    UCharacterConfigurationAsset * CharacterConfiguration;
    
    UPROPERTY(EditInstanceOnly, Category="Spawn")
    TArray<AActor *> PathPoints;

public :
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Spawn")
    TSubclassOf<ABaseCharacter> CharacterToSpawn;
    
    UFUNCTION(BlueprintCallable, Category="JD|Spawn Character")
    void Spawn();
	
};
