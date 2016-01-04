#include "BaseBlank.h"
#include "Interactables/HouseInteractableActor.h"
#include "HouseWPInteractionComponent.h"

UHouseWPInteractionComponent::UHouseWPInteractionComponent(const FObjectInitializer & PCIP) : Super(PCIP)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}



// Called when the game starts
void UHouseWPInteractionComponent::BeginPlay()
{
 Super::BeginPlay();
}


// Called every frame
void UHouseWPInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
 Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UHouseWPInteractionComponent::Interact(APawn * Target)
{
	Super::Interact(Target);

	AHouseInteractableActor * houseActor = (AHouseInteractableActor *)Cast<AHouseInteractableActor>(GetOwner());

	ensureMsgf(houseActor, TEXT("[HouseWPInteractionComponent] The house component needs an house interactable actor"));

	houseActor->AddPawn(Target);
}

bool UHouseWPInteractionComponent::IsInteractionWithTargetOver(APawn * Target)
{
	ensure(Target);

	AHouseInteractableActor * houseActor = (AHouseInteractableActor *)Cast<AHouseInteractableActor>(GetOwner());

	ensureMsgf(houseActor, TEXT("[HouseWPInteractionComponent] The house component needs an house interactable actor"));

	return houseActor->GetPawn(Target) != nullptr;
}

bool UHouseWPInteractionComponent::IsInteractingWithTarget(APawn * Target)
{
	ensure(Target);

	AHouseInteractableActor * houseActor = (AHouseInteractableActor *)Cast<AHouseInteractableActor>(GetOwner());

	ensureMsgf(houseActor, TEXT("[HouseWPInteractionComponent] The house component needs an house interactable actor"));

	return houseActor->GetPawn(Target) != nullptr;
}