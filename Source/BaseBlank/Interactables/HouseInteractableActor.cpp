

#include "BaseBlank.h"
#include "HouseInteractableActor.h"
#include "InteractableActorConfiguration.h"

AHouseInteractableActor::AHouseInteractableActor(const FObjectInitializer & PCIP) : Super(PCIP)
{
	ParticleSystem = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
	WaypointInteraction = PCIP.CreateDefaultSubobject<UHouseWPInteractionComponent>(this, TEXT("WaypointInteraction"));
	StartInteractionPoint = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StartInteractionPosition"));
	EndInteractionPoint = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("EndInteractionPosition"));

	WaypointInteraction->StartInteractionPoint = StartInteractionPoint;
	WaypointInteraction->EndInteractionPoint = EndInteractionPoint;

	SetRootComponent(ParticleSystem);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

float AHouseInteractableActor::NPCSCount()
{
	return NPCSInside.Num();
}

void AHouseInteractableActor::AddPawn(APawn* Pawn)
{
	ensure(Pawn);

	FPawnsStoredInHouse * npc = new FPawnsStoredInHouse({ Pawn, 0 });

	if (HasPawn(Pawn))
	{
		return;
	}

	//FIXME: As we dont have proper anims (yet) the actor will just get teleported inside the house
	
	if (HouseActor)
	{
		Pawn->SetActorLocation(HouseActor->GetActorLocation());
	}
	

	NPCSInside.Add(npc);
}

bool AHouseInteractableActor::HasPawn(APawn* Pawn)
{
	ensure(Pawn);

	if (GetPawn(Pawn))
	{
		return true;
	}

	return false;
}

inline FPawnsStoredInHouse * AHouseInteractableActor::GetPawn(APawn * Pawn)
{
	for (int i = 0; i < NPCSInside.Num(); i++)
	{
		if (NPCSInside[i]->Pawn == Pawn)
		{
			return NPCSInside[i];
		}
	}

	return nullptr;
}

float AHouseInteractableActor::PawnRemainingTime(APawn* Pawn)
{
	ensure(Pawn);

	FPawnsStoredInHouse * storedActor = GetPawn(Pawn);

	if (storedActor)
	{
		return WaypointInteraction->WaitTime - storedActor->PassedTime;
	}

	return 0;
}

void AHouseInteractableActor::BeginPlay()
{
	ensure(Configuration);

	ConfigurePowerInteractions(Configuration);
}

void AHouseInteractableActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (int i = 0; i < NPCSInside.Num(); i++)
	{
		NPCSInside[i]->PassedTime += DeltaSeconds;

		if (NPCSInside[i]->PassedTime > WaypointInteraction->WaitTime)
		{
			FPawnsStoredInHouse * stored  = NPCSInside[i];

			WaypointInteraction->OnActorInteractionOver(NPCSInside[i]->Pawn);

			//FIXME: As we dont have actual anims (yet) the actor will just get teleported to the end interaction point
			NPCSInside[i]->Pawn->SetActorLocation(EndInteractionPoint->GetComponentLocation());

			NPCSInside.RemoveSingle(NPCSInside[i]);
			delete stored;
			break;
		}
	}
}

bool operator==(const FPawnsStoredInHouse & LHS, FPawnsStoredInHouse & RHS)
{
	return LHS.Pawn == RHS.Pawn && LHS.PassedTime == RHS.PassedTime;
}
