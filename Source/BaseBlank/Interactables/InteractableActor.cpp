

#include "BaseBlank.h"
#include "InteractableActor.h"


// Sets default values
AInteractableActor::AInteractableActor(const FObjectInitializer & PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PowerInteraction = PCIP.CreateDefaultSubobject<UPowerInteractionsComponent>(this, TEXT("PowerInteractions"));
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AInteractableActor::ConfigurePowerInteractions(UInteractableActorConfiguration * Configuration)
{
	ensure(Configuration);

	for (auto & powerClass : Configuration->ShieldedFromPowers)
	{
		PowerInteraction->AddShieldedPower(powerClass);
	}
}

