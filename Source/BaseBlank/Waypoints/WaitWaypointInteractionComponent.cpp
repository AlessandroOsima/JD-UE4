#include "BaseBlank.h"
#include "WaitWaypointInteractionComponent.h"

UWaitWaypointInteractionComponent::UWaitWaypointInteractionComponent(const FObjectInitializer & PCIP) : Super(PCIP)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UWaitWaypointInteractionComponent::Interact(APawn * Target)
{
	if (!GetPawn(Target))
	{
		FPawnsWaiting * pawnsWaiting = new FPawnsWaiting({ Target, 0 });

		NPCSWaiting.Add(pawnsWaiting);
	}
}

bool UWaitWaypointInteractionComponent::IsInteractionWithTargetOver(APawn * Target)
{
	if (!GetPawn(Target))
	{
		return true;
	}

	return false;
}

bool UWaitWaypointInteractionComponent::IsInteractingWithTarget(APawn * Target)
{
	if (GetPawn(Target))
	{
		return true;
	}

	return false;
}

inline FPawnsWaiting * UWaitWaypointInteractionComponent::GetPawn(APawn * Pawn)
{
	for (int i = 0; i < NPCSWaiting.Num(); i++)
	{
		if (NPCSWaiting[i]->Pawn == Pawn)
		{
			return NPCSWaiting[i];
		}
	}

	return nullptr;
}

void UWaitWaypointInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (int i = 0; i < NPCSWaiting.Num(); i++)
	{
		NPCSWaiting[i]->PassedTime += DeltaTime;

		if (NPCSWaiting[i]->PassedTime > WaitTime)
		{
			FPawnsWaiting * stored = NPCSWaiting[i];

			OnInteractionOver().Broadcast(this, NPCSWaiting[i]->Pawn);

			//FIXME: As we dont have actual anims (yet) the actor will just get teleported to the end interaction point
			if (StartInteractionPoint != EndInteractionPoint || StartInteractionPoint->GetComponentLocation() != EndInteractionPoint->GetComponentLocation())
			{
				NPCSWaiting[i]->Pawn->SetActorLocation(EndInteractionPoint->GetComponentLocation());

			}
				
			NPCSWaiting.RemoveSingle(NPCSWaiting[i]);
			delete stored;
			break;
		}
	}
}
