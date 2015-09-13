#pragma once

#include "GameFramework/Actor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/Texture2D.h"
#include "UMG.h"
#include "UI/PowerWidget.h"
#include "BasePowerActor.generated.h"


class UPowerConfigurationAsset;
class ABaseCharacter;
class UBaseEffect;

/**
 * 
 */

//TODO: Effects should be assigned to an actor with a valid EffectComponent not only to a BaseCharacter
UCLASS(BlueprintType, Blueprintable)
class BASEBLANK_API ABasePowerActor : public AActor
{
	GENERATED_BODY()

	//Base Power Description
public:
	ABasePowerActor(const FObjectInitializer & PCIP);

	//The souls you have to spend to use this power
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    int32 SoulsCost;
    
	//This power human readable name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    FString Name;
    
	//The power description (used on the power widget tooltips and on the gui)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    FString Description;
    
	//The Behaviour tree to push on the target character (if hit)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    UBehaviorTree * BHTAsset;

	//If this can be used in conjuction with other effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Info")
	bool CanHaveChainedEffects;

	//The widget representing the power on the power bar
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    TSubclassOf<UPowerWidget> PowerWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Components")
	class UBoxComponent * BoxCollider;
public:
	//Common Powers Interface used by the camera raycast component

	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	bool CanUse();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void Use();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void Selecting();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void UnSelecting();    

	//Utility functions

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void SpendSouls();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool CanSpendWithoutLosing();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool ApplyEffectOnCharacter(TSubclassOf<UBaseEffect> Effect, ABaseCharacter * BaseCharacter);

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool ApplyEffectOnInteractableObject(TSubclassOf<UBaseEffect> Effect);

	//If BaseCharacter is shielded from this power
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool CanBeUsedOnThisCharacter(ABaseCharacter * BaseCharacter);

	//if this power can be used on BaseCharacter without losing the level
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool CanBeUsedOnThisCharacterWithoutLosing(ABaseCharacter * BaseCharacter);

	//If there are enough souls that can be spent to use this power
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool HasEnoughSoulsToSpend();

	//The power can be used on non shielded target with an effect component (a valid component) and enough souls
	//TODO: Handle with other actors than base character
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool CanBeUsedOnValidTarget();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool IsValidTarget(AActor * target);
};

