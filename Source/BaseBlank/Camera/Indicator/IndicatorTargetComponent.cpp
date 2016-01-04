

#include "BaseBlank.h"
#include "IndicatorTargetComponent.h"


// Sets default values for this component's properties
UIndicatorTargetComponent::UIndicatorTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UIndicatorTargetComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UIndicatorTargetComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

void UIndicatorTargetComponent::NotifyEndInteraction(UWaypointInteractionComponent & InteractionComponent)
{
	if (Indicator)
	{
		Indicator->TargetEndInteraction(&InteractionComponent);
	}
}

void UIndicatorTargetComponent::NotifyStartInteraction(UWaypointInteractionComponent & InteractionComponent)
{
	if (Indicator)
	{
		Indicator->TargetStartInteraction(&InteractionComponent);
	}
}

