// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GameModeInfo/FreeGameMode/FreeGameModeConfigurationAsset.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "BaseBlankGameMode.generated.h"

class UFreeModeSoulsInfoComponent;
class ANPCController;

/**
 * 
 */
UCLASS()
class BASEBLANK_API ABaseBlankGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
    
private:
    TArray<ANPCController *> m_npcs;
    
protected:
    virtual void HandleMatchIsWaitingToStart() override;
    
    virtual void HandleMatchHasStarted() override;
        
    virtual bool ReadyToEndMatch() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
    UFreeGameModeConfigurationAsset * GameModeConfig;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadonly)
    UFreeModeSoulsInfoComponent * SoulsManager;

public:
    
    UFUNCTION(BlueprintCallable, Category="JD,Victory Conditions")
    bool Lost() const;
    
    UFUNCTION(BlueprintCallable, Category="JD,Victory Conditions")
    bool Won() const;
    
    UFUNCTION(BlueprintCallable, Category="JD,Victory Conditions")
    FVictoryConditionsInfo & VictoryType() const;
    
    UFUNCTION(BlueprintCallable, Category="JD,Free Game Mode Info")
    float GetNPCSInState(ENPCBehaviour _state);
    
    UFUNCTION(BlueprintCallable, Category="JD,Free Game Mode Info")
    float GetNPCSNotInState(ENPCBehaviour _state);
    
    UFUNCTION(BlueprintCallable, Category="JD,Free Game Mode Info")
    float GetNPCSCount();
    
    UFUNCTION(BlueprintCallable, Category="JD, LevelInfo")
    FString GetCurrentLevelName();
    
private:
    
    void ListNPCS();
    
};
