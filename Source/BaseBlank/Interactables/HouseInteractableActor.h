

#pragma once

#include "Interactables/InteractableActor.h"
#include "NPCController/NPCController.h"
#include "Waypoints/HouseWPInteractionComponent.h"
#include "Interactables/HouseInteractableConfiguration.h"
#include "HouseInteractableActor.generated.h"

/**
 * 
 */

struct  FPawnsStoredInHouse
{
	APawn * Pawn;
	float PassedTime;
};

bool operator==(const FPawnsStoredInHouse & LHS, FPawnsStoredInHouse & RHS);

UCLASS()
class BASEBLANK_API AHouseInteractableActor : public AInteractableActor
{
	GENERATED_BODY()
private:
	TArray<FPawnsStoredInHouse *> NPCSInside;

public:
	
	AHouseInteractableActor(const FObjectInitializer & PCIP);
	
	//TODO: Should become skeletal for house door anim
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components")
	AActor * HouseActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent * ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Components")
	UHouseWPInteractionComponent * WaypointInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Points")
	UStaticMeshComponent * StartInteractionPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Points")
	UStaticMeshComponent * EndInteractionPoint;

	UFUNCTION(BlueprintCallable, Category = "JD|House Interactions")
	float NPCSCount();

	void AddPawn(APawn * Pawn);

    bool HasPawn(APawn * Pawn);

	//If this pawn is inside the house
	inline FPawnsStoredInHouse * GetPawn(APawn * Pawn);

	//The time the pawn still has to wait inside the house
	float PawnRemainingTime(APawn* Pawn);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
	UHouseInteractableConfiguration * Configuration;
};
