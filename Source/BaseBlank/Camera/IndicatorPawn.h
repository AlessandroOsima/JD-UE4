#pragma once

#include "GameFramework/Pawn.h"
#include "Waypoints/WaypointInteractionComponent.h"
#include "IndicatorPawn.generated.h"

UENUM(BlueprintType)
enum class EIndicatorTargetingState : uint8
{
	NoTarget,
	HoverOnTarget,
	MoveToTarget,
	OnTarget
};

UCLASS()
class BASEBLANK_API AIndicatorPawn : public APawn
{
	GENERATED_BODY()
private:

	AActor * Target = nullptr;
public:
	// Sets default values for this pawn's properties
	AIndicatorPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void ReceiveHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor);

	FORCEINLINE EIndicatorTargetingState GetIndicatorState();

protected:
	UFUNCTION(BlueprintCallable, Category="Indicator Target")
	void SetTarget(AActor * Target);

	UFUNCTION(BlueprintCallable, Category = "Indicator Target")
	void UnsetTarget();

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "JD|Indicator Target")
	void SwitchTargetState();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "JD|Indicator Target")
	void OnIndicatorStateChanged(EIndicatorTargetingState State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "JD|Indicator Target")
	void RemoveTarget();

	UFUNCTION(BlueprintCallable, Category = "JD|Indicator Target")
	AActor * GetTarget();

	UFUNCTION(BlueprintCallable, Category = "JD|Indicator Target")
	bool HasTarget();

	UFUNCTION(BlueprintCallable, Category = "JD|Indicator Target")
	void SetState(EIndicatorTargetingState State);

	void TargetStartInteraction(UWaypointInteractionComponent * Interaction);

	void TargetEndInteraction(UWaypointInteractionComponent * Interaction);

	UFUNCTION(BlueprintImplementableEvent, Category = "JD|Indicator Interaction Target")
	void OnTargetStartInteraction(UWaypointInteractionComponent * Interaction);

	UFUNCTION(BlueprintImplementableEvent, Category = "JD|Indicator Interaction Target")
	void OnTargetEndInteraction(UWaypointInteractionComponent * Interaction);

	//Scale the indicator to the sphere collider
	UFUNCTION(BlueprintCallable, Category = "JD|Indicator Size")
	void ScaleToSphereCollider(AActor * Actor);

	//The curve used for the scale function
	UPROPERTY(EditAnywhere, Category = "JD|Indicator Size")
	UCurveFloat * RayToScale;

private:

	UPROPERTY(EditAnywhere, Category = "Ground Collision", meta = (UIMin = 0, ClampMin = 0))
	float GroundRaycastLenght;

	UPROPERTY(EditAnywhere, Category = "Ground Collision", meta = (UIMin = 0, ClampMin = 0))
	float GroundDistance;

	UPROPERTY(EditAnywhere, Category = "Ground Collision", meta = (UIMin = 0, ClampMin = 0))
	TEnumAsByte<ECollisionChannel> GroundCollisionChannel;

	UPROPERTY(EditAnywhere, Category = "Ground Collision", meta = (UIMin = 0, ClampMin = 0))
	float Tolerance = 50.f;

	UPROPERTY(EditAnywhere, Category = "Ground Collision", meta = (UIMin = 0, ClampMin = 0))
	UCurveFloat * AccelerationOverDistance;

	float NormalStateAcceleration = 0;

	UFloatingPawnMovement * FloatingPawn;

	float MaxDistance = 0.f;

	EIndicatorTargetingState State = EIndicatorTargetingState::NoTarget;

	FVector ScaleToRestore;

	FVector TargetScale;

	bool EnableScaleTransform = false;
};
