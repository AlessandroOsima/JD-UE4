#pragma once

#include "Components/ActorComponent.h"
#include "WaypointInteractionComponent.generated.h"


//Interface for all interactions between a waypoint (like an house) and an actor
UCLASS(ClassGroup = (JD), abstract, BlueprintType)
class BASEBLANK_API UWaypointInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	//The params are the interactable component and the actor that is interacting
	DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractionOver, UWaypointInteractionComponent *, APawn*);
protected:

	FInteractionOver InteractionOverEvent;

public:

	UWaypointInteractionComponent(const FObjectInitializer & PCIP);
	
	//Must be set by owner actor as a visible property to make this visible and movable in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Points")
	UStaticMeshComponent * StartInteractionPoint;

	//Must be set by owner actor as a visible property to make this visible and movable in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Points")
	UStaticMeshComponent * EndInteractionPoint;

	//How much time (in seconds) the actor will wait inside at the interaction point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float WaitTime = 0;
	
	//Utility Functions

	UFUNCTION(BlueprintCallable, Category = "JD|InteractionPoint")
	FVector GetStartInteractionPointPosition() const
	{
		return StartInteractionPoint->GetComponentLocation();
	}

	UFUNCTION(BlueprintCallable, Category = "JD|InteractionPoint")
	FVector GetEndInteractionPointPosition() const
	{
		return EndInteractionPoint->GetComponentLocation();
	}
	///

	FInteractionOver & OnInteractionOver()
	{
		return InteractionOverEvent;
	}

	
	//Called when the game starts
	virtual void BeginPlay() override;
	
	/*
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	*/

	virtual void OnRegister() override;

	virtual void Interact(APawn * Target);

	virtual bool IsInteractionWithTargetOver(APawn * Target);

	virtual bool IsInteractingWithTarget(APawn * Target);
};
