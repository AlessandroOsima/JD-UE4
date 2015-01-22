// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "PathPointsComponent.h"


UPathPointsComponent::UPathPointsComponent(const class FObjectInitializer& PCIP)
: Super(PCIP), SpawnPoints()
{

}

void UPathPointsComponent::SetPathPoints(TArray<AActor *> _spawnPoints)
{
    SpawnPoints = _spawnPoints;
}

TArray<AActor *> UPathPointsComponent::GetPathPoints()
{
    return SpawnPoints;
}