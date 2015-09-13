// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "CameraPawn.h"
#include "Components/PowerRayCasterComponent.h"

ACameraPawn::ACameraPawn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    //UE_LOG(LogTemp, Log, TEXT("Spawning camera controller"));
    
    BoxCollider = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollider"));
    BoxCollider->SetBoxExtent(FVector(1,1,1),true);

    MovementComponent = PCIP.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovewmentComponent"));
    MovementComponent->UpdatedComponent = BoxCollider;
    
    RootComponent = BoxCollider;
    
    Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, FName("CameraComponent"));
    Camera->AttachTo(RootComponent);
    Camera->bUsePawnControlRotation = true;
    
    PowerService = PCIP.CreateDefaultSubobject<UPowerRayCasterComponent>(this, TEXT("PowerRayCasterComponent"));
    PowerService->PrimaryComponentTick.bCanEverTick = true;
}


void ACameraPawn::BeginPlay()
{
    Super::BeginPlay();
    MovementComponent->RegisterComponent();
    PowerService->RegisterComponent();
    
    //UE_LOG(LogTemp, Log, TEXT("Starting game"));
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent * _inputComponent)
{
    //Ignore default axis mappings
    //Super::SetupPlayerInputComponent(_inputComponent);
    
    check(InputComponent);
    
    _inputComponent->BindAxis("MoveForward", this, &ACameraPawn::MoveForward);
    _inputComponent->BindAxis("MoveSide", this, &ACameraPawn::MoveSide);
    _inputComponent->BindAxis("Zoom", this, &ACameraPawn::MoveUp);
    _inputComponent->BindAxis("RotateZ", this, &ACameraPawn::RotateZ);
    _inputComponent->BindAxis("RotateY", this, &ACameraPawn::RotateY);
    _inputComponent->BindAction("UsePower", IE_Pressed, this, &ACameraPawn::OnPowerUsed);
    _inputComponent->BindAction("PowerNext", IE_Pressed, this, &ACameraPawn::OnPowerNext);
    _inputComponent->BindAction("PowerPrev", IE_Pressed, this, &ACameraPawn::OnPowerPrevious);

	//Keyboard keys mapping to powers is done in tick, read the comments to know why
}

void ACameraPawn::MoveForward(float _value)
{
    if(_value != 0)
    {
        //UE_LOG(LogTemp, Log, TEXT("MOVE FORWARD WITH VALUE %f"), _value)
        
        FVector forward = TransformByCameraRotation(FVector(1,0,0), CameraForwardVector);
        
        this->AddMovementInput(forward,_value);
    }
}

FVector ACameraPawn::TransformByCameraRotation(const FVector & _toTransform, ECameraDirectionRotationType _rotationType) const
{
    FVector direction;
    
    switch (_rotationType)
    {
        case ECameraDirectionRotationType::Model :
        {
            direction = this->GetViewRotation().RotateVector(_toTransform);
            break;
        }
            
        case ECameraDirectionRotationType::ModelNoPitch :
        {
            FRotator r = this->GetViewRotation();
            FRotator target = FRotator(0, r.Yaw, r.Roll);
            
            direction = target.RotateVector(_toTransform);
            
            break;
        }
            
        case ECameraDirectionRotationType::ModelNoYaw :
        {
            FRotator r = this->GetViewRotation();
            FRotator target = FRotator(r.Pitch, 0, r.Roll);
            
            direction = target.RotateVector(_toTransform);
            
            break;
        }
            
        case ECameraDirectionRotationType::ModelNoRoll :
        {
            FRotator r = this->GetViewRotation();
            FRotator target = FRotator(r.Pitch, r.Yaw, 0);
            
            direction = target.RotateVector(_toTransform);
            
            break;
        }
    
        case ECameraDirectionRotationType::World :
        {
            direction = FVector(_toTransform);
            break;
        }
    }
    
    return direction;
}

void ACameraPawn::MoveSide(float _value)
{
    if(_value != 0)
    {
        //UE_LOG(LogTemp, Log, TEXT("MOVE SIDEWAYS WITH VALUE %f"), _value)
        
        FVector side = TransformByCameraRotation(FVector(0,1,0), CameraSideVector);
        
        this->AddMovementInput(side,_value);
    }
}

void ACameraPawn::RotateZ(float _value)
{
    if(_value)
    {
        //UE_LOG(LogTemp, Log, TEXT("ROTATE WITH VALUE %f"), _value)
        //UE_LOG(LogTemp, Log, TEXT("ROTATION STEP YAW IS %f"), RotationStepYaw)
        
        this->AddControllerYawInput(RotationStepYaw * _value);
    }
}

void ACameraPawn::RotateY(float _value)
{
    if(_value)
    {
        //UE_LOG(LogTemp, Log, TEXT("ROTATE WITH VALUE %f"), _value)
        //UE_LOG(LogTemp, Log, TEXT("ROTATION STEP IS %f"), RotationStepPitch)
        
        this->AddControllerPitchInput(RotationStepPitch * _value);
    }
}

void ACameraPawn::Tick(float _deltaTime)
{
	//READ
	//This is a pretty horrible solution BUT its the less terrible one since mapping an action and a function for each key is even crappier
	//and axis are not the solution as they get reset to zero when no button is pressed
    if(this->GetController())
    {
		APlayerController * controller = Cast<APlayerController>(GetController());

		if (controller)
		{
			if (controller->WasInputKeyJustPressed(EKeys::One))
			{
				PowerService->SelectPower(0);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Two))
			{
				PowerService->SelectPower(1);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Three))
			{
				PowerService->SelectPower(2);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Four))
			{
				PowerService->SelectPower(3);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Five))
			{
				PowerService->SelectPower(4);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Six))
			{
				PowerService->SelectPower(5);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Seven))
			{
				PowerService->SelectPower(6);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Eight))
			{
				PowerService->SelectPower(7);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Nine))
			{
				PowerService->SelectPower(8);
			}

			if (controller->WasInputKeyJustPressed(EKeys::Zero))
			{
				PowerService->SelectPower(9);
			}
		}
		
    }
}

void ACameraPawn::MoveUp(float _value)
{
    
    FVector up = TransformByCameraRotation(FVector(0,0,1), CameraUpVector);
    
    this->AddMovementInput(up,_value);
}

void ACameraPawn::OnPowerUsed()
{
    PowerService->UsePower();
}

void ACameraPawn::OnPowerNext()
{
    PowerService->SelectNextPower();
}

void ACameraPawn::OnPowerPrevious()
{
    PowerService->SelectPreviousPower();
}

UPawnMovementComponent * ACameraPawn::GetMovementComponent() const
{
    return MovementComponent;
}

