#include "BaseBlank.h"
#include "WaypointInteractionComponent.h"


// Sets default values for this component's properties
UWaypointInteractionComponent::UWaypointInteractionComponent(const FObjectInitializer & PCIP)
{
}

void UWaypointInteractionComponent::BeginPlay()
{
	/* We do this checks in begin play because OnRegister can be called outside 
	of game when adding the component to an actor()
	*/
	ensureMsgf(StartInteractionPoint, TEXT("[UWaypointInteractionComponent] We are expecting to have interaction start and end points "));
	ensureMsgf(EndInteractionPoint, TEXT("[UWaypointInteractionComponent] We are expecting to have interaction start and end points "));

	EndInteractionPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EndInteractionPoint->bCanEverAffectNavigation = false;
	StartInteractionPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartInteractionPoint->bCanEverAffectNavigation = true;
}

void UWaypointInteractionComponent::OnRegister()
{
	Super::OnRegister();
}

void UWaypointInteractionComponent::Interact(APawn * Target)
{

}

bool UWaypointInteractionComponent::IsInteractionWithTargetOver(APawn * Target)
{
	return true;
}

bool UWaypointInteractionComponent::IsInteractingWithTarget(APawn * Target)
{
	return false;
}

/*
// Called when the game starts
void UWaypointInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWaypointInteractionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
*/
