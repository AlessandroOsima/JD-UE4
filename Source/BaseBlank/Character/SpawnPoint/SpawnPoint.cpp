// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "SpawnPoint.h"
#include "Character/Configuration/CharacterConfigurationAsset.h"
#include "Engine/World.h"


ASpawnPoint::ASpawnPoint(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}


void ASpawnPoint::Spawn()
{
    m_rotator = this->GetTransform().GetRotation().Rotator();
    m_position = this->GetTransform().GetLocation();
    
	FActorSpawnParameters SpawnParams;
	SpawnParams.OverrideLevel = GetWorld()->GetCurrentLevel();
	SpawnParams.SpawnCollisionHandlingOverride = CollisionHandlingOnSpawn;

    AActor * spawnedActor = GetWorld()->SpawnActor(CharacterToSpawn, &m_position, &m_rotator, SpawnParams);
   
	if (spawnedActor)
	{
		ABaseCharacter * baseChr = Cast<ABaseCharacter>(spawnedActor);
		baseChr->SetCharacterConfiguration(CharacterConfiguration);
		baseChr->PathPointsComponent->SetPathPoints(PathPoints);
	}
}
