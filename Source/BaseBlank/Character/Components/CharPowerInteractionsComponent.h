

#pragma once

#include "Character/Components/EffectComponent.h"
#include "CharPowerInteractionsComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Logic, Common), editinlinenew, meta = (BlueprintSpawnableComponent))
class BASEBLANK_API UCharPowerInteractionsComponent : public UPowerInteractionsComponent
{
	GENERATED_BODY()

	virtual void OnRegister() override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnCharacterStateChange(ABaseCharacter * Character, ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior);
};
