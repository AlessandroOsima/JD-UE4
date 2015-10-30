#pragma once

#include "Engine/DataAsset.h"
#include "Powers/BasePowerActor.h"
#include "InteractableActorConfiguration.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UInteractableActorConfiguration : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<TSubclassOf<ABasePowerActor>> ShieldedFromPowers;
};
