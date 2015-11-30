// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "CameraPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerCamera, Log, All);

UENUM(BlueprintType)
enum class ECameraDirectionRotationType : uint8
{
    World, //Do not rotate direction using the object rotation
    Model, //Rotate direction using the object rotation
    ModelNoPitch, //Use object rotation for roll and yaw
    ModelNoYaw, //Use object rotation for roll and pitch
    ModelNoRoll, //Use object rotation for yaw and pitch
};

class UPowerRayCasterComponent;

/**
 * 
 */
UCLASS()
class BASEBLANK_API ACameraPawn : public APawn
{
	GENERATED_UCLASS_BODY()
    
public:
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraForwardVector = ECameraDirectionRotationType::World;
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraSideVector = ECameraDirectionRotationType::World;
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraUpVector = ECameraDirectionRotationType::World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationStep = 90;

	UPROPERTY(EditDefaultsOnly, Category = "Rotation")
	UCurveFloat * RotationStepOverInputStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Indicator Target")
	APawn * Indicator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Indicator Target")
	FVector OffsetFromIndicator = FVector(0, -100, 50);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Powers")
    UPowerRayCasterComponent * PowerService;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    class UCameraComponent * Camera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
    class UPawnMovementComponent * MovementComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Collision)
    class USphereComponent * SphereCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	int32 StartZoomDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float LowerZoomRangeCap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float HigherZoomRangeCap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float ZoomAccelerationStep = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float ZoomAccelerationMax = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	UCurveFloat * ZoomStepOverInputStrenght;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TArray<TEnumAsByte<ECollisionChannel>> CameraCollisionChannels;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	bool DoComplexTrace = false;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	float ForwardRaycastSize = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	float SideRaycastSize = 5;


    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent * _inputComponent) override;
    
    void MoveForward(float _value);
    void MoveSide(float _value);
    void MoveUp(float _value);
    void RotateZ(float _value);
    void OnPowerUsed();
    void OnPowerNext();
    void OnPowerPrevious();
    
    virtual UPawnMovementComponent * GetMovementComponent() const override;
    virtual void Tick(float _deltaTime);

private:
    FVector TransformByCameraRotation(const FVector & _toTransform, ECameraDirectionRotationType _rotationType) const;
    
	float RotationDirection = 0;
	FRotator CurrentRotation{ 0, 0, 0 };

	float ZoomDistance = 0;
	float ZoomDirection = 0;
	float ZoomSpeed = 0;
	float ZoomAcceleration = 0;

	int DebugPathLocationCounter = 0;

	FVector OldIndicatorPosition;
};
