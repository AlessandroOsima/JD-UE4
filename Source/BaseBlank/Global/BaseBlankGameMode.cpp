// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BaseBlankGameMode.h"
#include "Camera/CameraPawn.h"
#include "Character/SpawnPoint/SpawnPoint.h"
#include "GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
#include "NPCController/NPCController.h"
#include "NPCController/Components/BehaviourComponent.h"
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

bool ABaseBlankGameMode::ReadyToEndMatch()
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


bool ABaseBlankGameMode::Lost() const
{
    if(SoulsManager->GetSoulsAmount() < GameModeConfig->LoseConditionSouls)
    {
        return true;
    }
    
    return false;
}

bool ABaseBlankGameMode::Won() const
{
    bool won = true;
    
    for(int i = 0; i < m_npcs.Num(); i++)
    {
        if(m_npcs[i]->BehaviourComponent->GetNPCBehaviour() != ENPCBehaviour::Dead)
        {
            won = false;
            break;
        }
    }
    
    return  won;
}

FVictoryConditionsInfo & ABaseBlankGameMode::VictoryType() const
{
    //You need a valid victory condition here. If you don't have one then wtf are you calling this function for ?
    ensureMsg(GameModeConfig->VictoriesCounditionSouls.Num() != 0, TEXT("[ABaseBlankGameMode]No Specified victory conditions"));
    
    for(int i = 0; i < GameModeConfig->VictoriesCounditionSouls.Num(); i++)
    {
        if(SoulsManager->GetSoulsAmount() < GameModeConfig->VictoriesCounditionSouls[i].SoulsAmount)
        {
            return GameModeConfig->VictoriesCounditionSouls[i];
        }
    }
    
    return GameModeConfig->VictoriesCounditionSouls[0];
}

float ABaseBlankGameMode::GetNPCSInState(ENPCBehaviour _state)
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

FString ABaseBlankGameMode::GetCurrentLevelName()
{
    FString prefixedMapName = GetWorld()->GetMapName();

    prefixedMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    
    return prefixedMapName;
}
