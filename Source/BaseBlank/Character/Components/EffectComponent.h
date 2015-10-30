#pragma once

#include "Character/Components/BaseCharacterComponent.h"
#include "Character/Effects/BaseEffect.h"
#include "EffectComponent.generated.h"

/**
 * This component has to be attached to an actor that can be influenced by a power effect
 *
 */
UCLASS()
class BASEBLANK_API UPowerInteractionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//TODO: The array is public, and we have an interface. Should the array be private ??
	//All the effects applied to this actor
	UPROPERTY(BlueprintReadOnly, Category="Powers") 
	TArray<UBaseEffect *> Effects;

	//Add a new effect to the effects list
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	void AddEffect(UBaseEffect * effect);

	//Remove an effect from the effect list
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	void RemoveEffect(UBaseEffect * effect);

	//Remove all the effects from the effect list
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	void RemoveAllEffects();

	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	bool HasEffectOfClass(TSubclassOf<UBaseEffect> Class, bool AlsoChild = true, bool AlsoParent = true) const;

	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	bool HasEffects() const;

	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	UBaseEffect * HigherPriorityEffect() const;

	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	bool HigherPriorityEffectIsOfClass(TSubclassOf<UBaseEffect> Class) const;

	//Power Shield Interface

	//This are the power actor that cannot influence this power
	UPROPERTY(EditDefaultsOnly, Category = "Powers")
	TArray<TSubclassOf<ABasePowerActor>> ShieldedFromPowers;

	//Add a power to this actor shielded powers list
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	void AddShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower);

	//Remove a power to this actor shielded powers list
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	void RemoveShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower);

	//Is this actor shielded from this power
	UFUNCTION(BlueprintCallable, Category = "JD|Power Component")
	bool IsShieldedFromPower(TSubclassOf<ABasePowerActor> shieldedPower);


protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


};
