// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "CameraPawn.generated.h"

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
    UPROPERTY(EditAnywhere, Category="Camera Step Rotation")
    float RotationStepYaw = 0.5f;
    
    UPROPERTY(EditAnywhere, Category="Camera Step Rotation")
    float RotationStepPitch = 0.5f;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Yaw Rotation")
	bool EnableYawRotation = true;

	//The higher limit on roation angle allowed in the [270-360] range. PitchPositiveRange must be > PitchNegativeRange
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "270.0", ClampMax = "360.0", UIMin = "270.0", UIMax = "360.0"), Category = "Pitch Rotation")
	float PitchPositiveRange = 360;
	
	//The lower limit on roation angle allowed in the [270-360] range. PitchNegativeRange must be > PitchPositiveRange
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "270.0", ClampMax = "360.0", UIMin = "270.0", UIMax = "360.0"), Category = "Pitch Rotation")
	float PitchNegativeRange = 270;

	//Enable rotation around pitch (z) axis
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pitch Rotation")
	bool EnablePitchRotation = true;
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraForwardVector = ECameraDirectionRotationType::World;
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraSideVector = ECameraDirectionRotationType::World;
    
    UPROPERTY(EditAnywhere, Category="Camera")
    ECameraDirectionRotationType CameraUpVector = ECameraDirectionRotationType::World;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Powers")
    UPowerRayCasterComponent * PowerService;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    class UCameraComponent * Camera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
    class UPawnMovementComponent * MovementComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Collision)
    class UBoxComponent * BoxCollider;

	
    
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent * _inputComponent) override;
    
    void MoveForward(float _value);
    void MoveSide(float _value);
    void MoveUp(float _value);
    void RotateZ(float _value);
    void RotateY(float _value);
    void OnPowerUsed();
    void OnPowerNext();
    void OnPowerPrevious();
    
    virtual UPawnMovementComponent * GetMovementComponent() const override;
    virtual void Tick(float _deltaTime);

private:
    FVector TransformByCameraRotation(const FVector & _toTransform, ECameraDirectionRotationType _rotationType) const;
    
};
