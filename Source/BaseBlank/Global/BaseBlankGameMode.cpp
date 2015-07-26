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
	: Super(PCIP)
{
    
    SoulsManager = PCIP.CreateDefaultSubobject<UFreeModeSoulsInfoComponent>(this, TEXT("Souls Manager"));
    
    //// set default pawn class to our Blueprinted character
    //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player_Camera"));
    //
    //if (PlayerPawnBPClass.Class != NULL)
    //{
    //    DefaultPawnClass = PlayerPawnBPClass.Class;
    //}
}

void ABaseBlankGameMode::HandleMatchIsWaitingToStart()
{
    UWorld* World = GetWorld();

    for (TActorIterator<ASpawnPoint> It(World); It; ++It)
    {
        It->Spawn();
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
    
    SoulsManager->SetGameModeInfoConfig(GameModeConfig);
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
	ensureMsg(GameModeConfig->VictoriesConditionNPCs.Num() != 0, TEXT("[ABaseBlankGameMode]No Specified victory conditions"));
    
	if (ActiveEffects.Num() == 0 && SoulsManager->GetSoulsAmount() <= GameModeConfig->LoseConditionSouls && GetNPCSInState(ENPCBehaviour::Dead) < GameModeConfig->VictoriesConditionNPCs[0].NPCsAmount)
	{
		return true;
	}

    return false;
}

bool ABaseBlankGameMode::Won() const
{
	return !Lost() && SoulsManager->GetSoulsAmount() <= GameModeConfig->LoseConditionSouls && ActiveEffects.Num() == 0;
}

FVictoryConditionsInfo & ABaseBlankGameMode::VictoryType() const
{
    //You need a valid victory condition here. If you don't have one then wtf are you calling this function for ?
    ensureMsg(GameModeConfig->VictoriesConditionNPCs.Num() != 0, TEXT("[ABaseBlankGameMode]No Specified victory conditions"));
    
	FVictoryConditionsInfo & conditions = GameModeConfig->VictoriesConditionNPCs[0];

	for(int i = 0; i < GameModeConfig->VictoriesConditionNPCs.Num(); i++)
    {
        if(GetNPCSInState(ENPCBehaviour::Dead) > GameModeConfig->VictoriesConditionNPCs[i].NPCsAmount && i > 0)
        {
            conditions = GameModeConfig->VictoriesConditionNPCs[i - 1];
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
