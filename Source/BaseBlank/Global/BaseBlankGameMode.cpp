// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BaseBlankGameMode.h"
#include "Camera/CameraPawn.h"
#include "Character/SpawnPoint/SpawnPoint.h"
#include "GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
#include "NPCController/NPCController.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "Character/Effects/BaseEffect.h"
#include "Character/BaseCharacter.h"
#include "EngineUtils.h"

ABaseBlankGameMode::ABaseBlankGameMode(const class FObjectInitializer& PCIP)
	: Super(PCIP), CanUnPause(true)
{
	SoulsManager = PCIP.CreateDefaultSubobject<UFreeModeSoulsInfoComponent>(this, TEXT("Souls Manager"));
	//Unpauser.BindUObject(this, &ABaseBlankGameMode::UnpauserDelegate);
	Pausers.Add(Unpauser);
}

void ABaseBlankGameMode::HandleMatchIsWaitingToStart()
{
	
    UWorld* World = GetWorld();

    for (TActorIterator<ASpawnPoint> It(World); It; ++It)
    {
		if (It->EnableSpawn)
		{
			It->Spawn();
		}
		
    }
    
    Super::HandleMatchIsWaitingToStart();
}

void ABaseBlankGameMode::ListNPCS()
{
    if(m_npcs.Num() > 0)
    {
        m_npcs.Empty();
    }
    
    UWorld* World = GetWorld();
    
    for (TActorIterator<ANPCController> It(World); It; ++It)
    {
        m_npcs.Add(*It);
    }
}

void ABaseBlankGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    
    ListNPCS();
}

bool ABaseBlankGameMode::ReadyToEndMatch_Implementation()
{
    if(Won())
    {
        return true;
    }
    
    if(Lost())
    {
        return true;
    }
    
    return false;
}


void ABaseBlankGameMode::StartPlay()
{
	SoulsManager->SetGameModeInfoConfig(GameModeConfig);

	Super::StartPlay();
}

void ABaseBlankGameMode::AddActiveEffect(UBaseEffect * activeEffect)
{
	ActiveEffects.Add(activeEffect);
}

void ABaseBlankGameMode::RemoveActiveEffect(UBaseEffect * effectToDeactivate)
{
	ActiveEffects.Remove(effectToDeactivate);
}

int32 ABaseBlankGameMode::GetActiveEffectsCount()
{
	return ActiveEffects.Num();
}


//Victory/Loss happens when there are no active effects, there are no more souls and the dead npcs are enough (or not) to win (or lose)
bool ABaseBlankGameMode::Lost() const
{
	ensureMsgf(GameModeConfig->VictoriesConditionNPCs.Num() != 0, TEXT("[ABaseBlankGameMode]No Specified victory conditions"));
    

	bool soulsEmpty = SoulsManager->GetSoulsAmount() <= GameModeConfig->LoseConditionSouls;
	bool notEnoughNPCs = GetNPCSInState(ENPCBehaviour::Dead) < GameModeConfig->VictoriesConditionNPCs[0].NPCsAmount;

	if (ActiveEffects.Num() == 0 && soulsEmpty && notEnoughNPCs)
	{
		return true;
	}

    return false;
}

bool ABaseBlankGameMode::Won() const
{
	bool enoughNPCs = GetNPCSInState(ENPCBehaviour::Dead) >= GameModeConfig->VictoriesConditionNPCs[0].NPCsAmount;
	bool soulsEmpty = SoulsManager->GetSoulsAmount() <= GameModeConfig->LoseConditionSouls;

	if (ActiveEffects.Num() == 0 && enoughNPCs)
	{
		if (!soulsEmpty && GetNPCSInState(ENPCBehaviour::Dead) < m_npcs.Num())
		{
			return false;
		}

		return true;
	}

	return false;
}

FVictoryConditionsInfo & ABaseBlankGameMode::VictoryType() const
{
    //You need a valid victory condition here. If you don't have one then wtf are you calling this function for ?
	ensureMsgf(GameModeConfig->VictoriesConditionNPCs.Num() != 0, TEXT("[ABaseBlankGameMode]No Specified victory conditions"));
    
	FVictoryConditionsInfo & conditions = GameModeConfig->VictoriesConditionNPCs[0];

	float deadNPCs = GetNPCSInState(ENPCBehaviour::Dead);

	for(int i = 0; i < GameModeConfig->VictoriesConditionNPCs.Num(); i++)
    {
        if(deadNPCs >= GameModeConfig->VictoriesConditionNPCs[i].NPCsAmount && i > 0)
        {
            conditions = GameModeConfig->VictoriesConditionNPCs[i];
        }
    }
    
    return conditions;
}

float ABaseBlankGameMode::GetNPCSInState(ENPCBehaviour _state) const
{
    int inState = 0;
    
    for(int i = 0; i < m_npcs.Num(); i++)
    {
        if(m_npcs[i]->BehaviourComponent->GetNPCBehaviour() == _state)
        {
            inState++;
        }
    }
    
    return inState;
}

float ABaseBlankGameMode::GetNPCSNotInState(ENPCBehaviour _state)
{
    int inState = 0;
    
    for(int i = 0; i < m_npcs.Num(); i++)
    {
        if(m_npcs[i]->BehaviourComponent->GetNPCBehaviour() != _state)
        {
            inState++;
        }
    }
    
    return inState;
}

float ABaseBlankGameMode::GetNPCSCount()
{
    return m_npcs.Num();
}

TArray<ANPCController*> & ABaseBlankGameMode::GetNPCs()
{
	return m_npcs;
}

FString ABaseBlankGameMode::GetEndGameDescription()
{
	FString description;
	if (Lost())
	{
		description = "YOU LOST";
	}
	else
	{
		description = VictoryType().VictoryText;
	}

	return description;
}

bool ABaseBlankGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate /*= FCanUnpause()*/)
{
	bool result = Super::SetPause(PC, CanUnpauseDelegate);
	if (result)
	{
		OnPauseToggle(true);
	}
	return result;
}

void ABaseBlankGameMode::ClearPause()
{
	if (CanUnPause)
	{
		Super::ClearPause();
		OnPauseToggle(false);
	}
}

void ABaseBlankGameMode::SetCanUnpause(bool CanUnpause)
{
	this->CanUnPause = CanUnPause;
}

const TArray<UBaseEffect *> & ABaseBlankGameMode::GetActiveEffects() const
{
	return ActiveEffects;
}

FString ABaseBlankGameMode::GetCurrentLevelName()
{
    FString prefixedMapName = GetWorld()->GetMapName();

    prefixedMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    
    return prefixedMapName;
}
