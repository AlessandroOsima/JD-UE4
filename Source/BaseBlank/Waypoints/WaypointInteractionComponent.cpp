#include "BaseBlank.h"
#include "Camera/Indicator/IndicatorTargetComponent.h"
#include "WaypointInteractionComponent.h"


void UWaypointInteractionComponent::OnActorInteractionOver(APawn * Target)
{
	ensure(Target);

	UIndicatorTargetComponent * indicatorTarget = GetIndicatorComponentFromPawn(Target);

	if (indicatorTarget)
	{
		indicatorTarget->NotifyEndInteraction(*this);
	}

	InteractionOverEvent.Broadcast(this, Target);
}

UIndicatorTargetComponent * UWaypointInteractionComponent::GetIndicatorComponentFromPawn(APawn * Pawn)
{
	ensure(Pawn);

	UIndicatorTargetComponent * indicatorTarget = (UIndicatorTargetComponent *)Pawn->GetComponentByClass(UIndicatorTargetComponent::StaticClass());

	if (!indicatorTarget)
	{
		indicatorTarget = (UIndicatorTargetComponent *)Pawn->GetController()->GetComponentByClass(UIndicatorTargetComponent::StaticClass());
	}

	return indicatorTarget;
}

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
	ensure(Target);

	UIndicatorTargetComponent * indicatorTarget = GetIndicatorComponentFromPawn(Target);

	if (indicatorTarget)
	{
		indicatorTarget->NotifyStartInteraction(*this);
	}
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
