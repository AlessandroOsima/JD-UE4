

#pragma once

#include "Waypoints/WaypointInteractionComponent.h"
#include "HouseWPInteractionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UHouseWPInteractionComponent : public UWaypointInteractionComponent
{
	GENERATED_BODY()

public:

	UHouseWPInteractionComponent(const FObjectInitializer & PCIP);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
		
	virtual void Interact(APawn * Target) override;

	virtual bool IsInteractionWithTargetOver(APawn * Target) override;

	virtual bool IsInteractingWithTarget(APawn * Target) override;

	virtual void OnActorInteractionOver(APawn * Target);
};
