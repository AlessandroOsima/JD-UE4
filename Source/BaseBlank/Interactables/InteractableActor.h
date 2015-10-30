#pragma once

#include "GameFramework/Actor.h"
#include "Character/Components/EffectComponent.h"
#include "Interactables/InteractableActorConfiguration.h"
#include "InteractableActor.generated.h"

//Actors that powers can interact with (aka has a UPowerInteractionsComponent and a config)
UCLASS()
class BASEBLANK_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor(const FObjectInitializer & PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Components")
	UPowerInteractionsComponent * PowerInteraction;

	UFUNCTION(BlueprintCallable, Category = "JD|Configuration")
	void ConfigurePowerInteractions(UInteractableActorConfiguration * Configuration);
};
