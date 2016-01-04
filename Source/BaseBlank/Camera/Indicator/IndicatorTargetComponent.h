

#pragma once

#include "Components/ActorComponent.h"
#include "Waypoints/WaypointInteractionComponent.h"
#include "Camera/IndicatorPawn.h"
#include "IndicatorTargetComponent.generated.h"


/*
An object that can be targeted by the indicator, this allows notification on interactions that change the state 
of the actor 
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASEBLANK_API UIndicatorTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIndicatorTargetComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void NotifyStartInteraction(UWaypointInteractionComponent & InteractionComponent);

	virtual void NotifyEndInteraction(UWaypointInteractionComponent & InteractionComponent);

	FORCEINLINE void SetIndicator(AIndicatorPawn * Indicator)
	{
		this->Indicator = Indicator;
	}

	FORCEINLINE AIndicatorPawn * GetIndicator()
	{
		return Indicator;
	}

private:

	AIndicatorPawn * Indicator = nullptr;
};
