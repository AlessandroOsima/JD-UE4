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

class UBaseEffect;
class ABaseCharacter;

UCLASS()
class BASEBLANK_API ABaseBlankGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
    
private:
    TArray<ANPCController *> m_npcs;

	TArray<UBaseEffect *> ActiveEffects;
    
protected:
    virtual void HandleMatchIsWaitingToStart() override;
    
    virtual void HandleMatchHasStarted() override;

	virtual bool ReadyToEndMatch_Implementation() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
    UFreeGameModeConfigurationAsset * GameModeConfig;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadonly)
    UFreeModeSoulsInfoComponent * SoulsManager;

public:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "JD|Victory Conditions")
	void AddActiveEffect(UBaseEffect * activeEffect);

	UFUNCTION(BlueprintCallable, Category = "JD|Victory Conditions")
	void RemoveActiveEffect(UBaseEffect * effectToDeactivate);

	UFUNCTION(BlueprintCallable, Category = "JD|Victory Conditions")
	int32 GetActiveEffectsCount();

    UFUNCTION(BlueprintCallable, Category="JD|Victory Conditions")
    bool Lost() const;
    
    UFUNCTION(BlueprintCallable, Category="JD|Victory Conditions")
    bool Won() const;
    
    UFUNCTION(BlueprintCallable, Category="JD|Victory Conditions")
    FVictoryConditionsInfo & VictoryType() const;
    
    UFUNCTION(BlueprintCallable, Category="JD|Free Game Mode Info")
    float GetNPCSInState(ENPCBehaviour _state) const;
    
    UFUNCTION(BlueprintCallable, Category="JD|Free Game Mode Info")
    float GetNPCSNotInState(ENPCBehaviour _state);
    
    UFUNCTION(BlueprintCallable, Category="JD|Free Game Mode Info")
    float GetNPCSCount();

	UFUNCTION(BlueprintCallable, Category = "JD|Free Game Mode Info")
	TArray<ANPCController *> & GetNPCs();

	UFUNCTION(BlueprintCallable, Category="JD|Level Info")
    FString GetCurrentLevelName();

	UFUNCTION(BlueprintCallable, Category = "JD|Level Info")
	FString GetEndGameDescription(); 

	UFUNCTION(BlueprintCallable, Category = "JD|Level Info")
	const TArray<UBaseEffect *> & GetActiveEffects() const;

	/** PAUSE OVERRIDES
	* Overrides to hook in the OnPauseToggle event that can be used in BPs to do UI spawning on pause
	*/
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual void ClearPause() override;

	FCanUnpause Unpauser;

	void SetCanUnpause(bool CanUnpause);

	UFUNCTION(BlueprintImplementableEvent, Category = "JD|Game Mode Management")
	void OnPauseToggle(bool Paused);
    
private:
    
    void ListNPCS();

protected:

	UPROPERTY(BlueprintReadWrite, Category="JD|Game Mode Management")
	bool CanUnPause;
    
};
