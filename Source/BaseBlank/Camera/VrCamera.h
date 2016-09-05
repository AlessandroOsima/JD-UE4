

#pragma once

#include "GameFramework/Pawn.h"
#include "Components/PowerRayCasterComponent.h"
#include "VrCamera.generated.h"

UCLASS()
class BASEBLANK_API AVrCamera : public APawn
{
	GENERATED_BODY()

public:

	AVrCamera(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="JD|Powers")
	UPowerRayCasterComponent * PowerRaycaster;

	UFUNCTION(BlueprintCallable, Category="JD|Powers")
	bool DoTargetRaycast(FVector StartLocation, FVector EndLocation, TEnumAsByte<ECollisionChannel> FloorChannel);
	
	UFUNCTION(BlueprintCallable, Category = "JD|VR Movement")
	void TeleportToLastValidPosition();

	UPROPERTY(BlueprintReadOnly, Category = "JD|Powers")
	FVector LastValidPosition;

	UPROPERTY(BlueprintReadOnly, Category = "JD|Powers")
	bool    bLastPositionIsValid;
	
};
