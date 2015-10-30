

#pragma once

#include "Waypoints/WaypointInteractionComponent.h"
#include "WaitWaypointInteractionComponent.generated.h"

/**
 * 
 */
struct  FPawnsWaiting
{
	APawn * Pawn;
	float PassedTime;
};

UCLASS(ClassGroup = (JD), BlueprintType, meta = (BlueprintSpawnableComponent))
class BASEBLANK_API UWaitWaypointInteractionComponent : public UWaypointInteractionComponent
{
	GENERATED_BODY()

private:

	TArray<FPawnsWaiting *> NPCSWaiting;

public:

	UWaitWaypointInteractionComponent(const FObjectInitializer & PCIP);

	virtual void Interact(APawn * Target);

	virtual bool IsInteractionWithTargetOver(APawn * Target);

	virtual bool IsInteractingWithTarget(APawn * Target);

	inline FPawnsWaiting * GetPawn(APawn * Pawn);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
