// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "CameraPawn.h"
#include "Components/PowerRayCasterComponent.h"
#include "Kismet/GameplayStatics.h"
#include "IndicatorPawn.h"

DEFINE_LOG_CATEGORY(PlayerCamera);

ACameraPawn::ACameraPawn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    //UE_LOG(LogTemp, Log, TEXT("Spawning camera controller"));
   

    MovementComponent = PCIP.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovewmentComponent"));
    MovementComponent->UpdatedComponent = SphereCollider;
    
	Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, FName("CameraComponent"));
	Camera->bUsePawnControlRotation = true;

    RootComponent = Camera;
    
	SphereCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BoxCollider"));
	SphereCollider->SetSphereRadius(10);
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
    
    PowerService = PCIP.CreateDefaultSubobject<UPowerRayCasterComponent>(this, TEXT("PowerRayCasterComponent"));
    PowerService->PrimaryComponentTick.bCanEverTick = true;
}


void ACameraPawn::BeginPlay()
{
    Super::BeginPlay();
	UWorld* World = GetWorld();

	for (TActorIterator<AIndicatorPawn> It(World); It; ++It)
	{
		Indicator = *It;
		break;
	}

    MovementComponent->RegisterComponent();
    PowerService->RegisterComponent();

	ZoomDistance = StartZoomDistance;
    
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
    //_inputComponent->BindAxis("RotateY", this, &ACameraPawn::RotateY);
    _inputComponent->BindAction("UsePower", IE_Pressed, this, &ACameraPawn::OnPowerUsed);
    _inputComponent->BindAction("PowerNext", IE_Pressed, this, &ACameraPawn::OnPowerNext);
    _inputComponent->BindAction("PowerPrev", IE_Pressed, this, &ACameraPawn::OnPowerPrevious);

	auto & actionBinding = _inputComponent->BindAction("TogglePause", IE_Pressed, this, &ACameraPawn::OnTogglePause);
	actionBinding.bExecuteWhenPaused = 1;

	//Keyboard keys mapping to powers is done in tick, read the comments to know why
}

void ACameraPawn::MoveForward(float _value)
{
    if(_value != 0)
    {

		FVector forward = TransformByCameraRotation(FVector(1, 0, 0), CameraForwardVector);
		if (Indicator)
		{
			FHitResult OutHit;

			FCollisionObjectQueryParams ObjectParams;
			FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
			QueryParams.bTraceComplex = DoComplexTrace;

			for (auto channel : CameraCollisionChannels)
			{
				ObjectParams.AddObjectTypesToQuery(channel);
			}

			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + forward * _value * ForwardRaycastSize, FColor::Green, true, 1.f);

			if (!GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + forward * _value * ForwardRaycastSize, ObjectParams, QueryParams))
			{
				//FString Forward = FString::Printf(TEXT("Forward move %s"), *forward.ToCompactString());
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, Forward);

				OldIndicatorPosition = Indicator->GetActorLocation();
				Indicator->AddMovementInput(forward, _value);
			}
		}
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
        
        //FVector side = TransformByCameraRotation(FVector(0,1,0), CameraSideVector);
        
        //this->AddMovementInput(side,_value);

		FVector side = TransformByCameraRotation(FVector(0, 1, 0), CameraSideVector);

		if (Indicator)
		{
			FHitResult OutHit;

			FCollisionObjectQueryParams ObjectParams;
			FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
			QueryParams.bTraceComplex = DoComplexTrace;

			for (auto channel : CameraCollisionChannels)
			{
				ObjectParams.AddObjectTypesToQuery(channel);
			}

			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + side * _value * SideRaycastSize, FColor::Red, true, 1.f);
			//DrawDebugSolidBox(GetWorld(), GetActorLocation(), FVector(0.1f, 0.1f, 0.1f), FColor::Green, false, 5.f);
			//DrawDebugSolidBox(GetWorld(), GetActorLocation() + side * _value * SideRaycastSize, FVector(0.1f, 0.1f, 0.1f), FColor::Red, false, 5.f);


			if (!GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + side * _value * SideRaycastSize, ObjectParams, QueryParams))
			{
				//FString Side = FString::Printf(TEXT("Side move %s"), *side.ToCompactString());
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, Side);

				OldIndicatorPosition = Indicator->GetActorLocation();
				Indicator->AddMovementInput(side, _value);
			}

		}
	
    }
}

void ACameraPawn::RotateZ(float _value)
{
	RotationDirection = _value;
}

void ACameraPawn::Tick(float _deltaTime)
{
	if (Indicator)
	{
		ensure(RotationStepOverInputStrenght);
		ensure(ZoomStepOverInputStrenght);

		float RotationStep = RotationStepOverInputStrenght->GetFloatValue(FMath::Abs(RotationDirection));

		if (RotationDirection > 0)
		{
			RotationStep *= -1;
		}

		FRotator NextRotation = CurrentRotation + FRotator(0, RotationStep * _deltaTime, 0);

		FVector ZoomedOffsetFromIndicator = OffsetFromIndicator;
		ZoomedOffsetFromIndicator.Normalize();

		float NextZoomDistance = ZoomDistance;

		float ZoomStep = ZoomStepOverInputStrenght->GetFloatValue(FMath::Abs(ZoomDirection));

		if (ZoomDirection < 0)
		{
			ZoomStep *= -1;
		}
			
		NextZoomDistance = ZoomDistance + ZoomStep * _deltaTime;

		NextZoomDistance = FMath::Clamp(NextZoomDistance, LowerZoomRangeCap, HigherZoomRangeCap);

		ZoomedOffsetFromIndicator = ZoomedOffsetFromIndicator * NextZoomDistance;
	

		FVector rotatedDirection = NextRotation.RotateVector(ZoomedOffsetFromIndicator);
		FVector position = Indicator->GetActorLocation() + rotatedDirection;
		FVector direction = Indicator->GetActorLocation() - position;
		direction.Normalize();

		FRotator rotation = direction.Rotation();
		
		FHitResult OutHit;
		
		FCollisionObjectQueryParams ObjectParams;
		FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
		QueryParams.bTraceComplex = DoComplexTrace;

		for (auto channel : CameraCollisionChannels)
		{
			ObjectParams.AddObjectTypesToQuery(channel);
		}

		if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), position, ObjectParams, QueryParams))
		{
			//DrawDebugLine(GetWorld(), GetActorLocation(), position, FColor::Yellow, true, 5.f);
			//DrawDebugSolidBox(GetWorld(), OutHit.Location, FVector(0.1f, 0.1f, 0.1f), FColor::Red, false, 5.f);
			//DrawDebugSolidBox(GetWorld(), position, FVector(0.1f, 0.1f, 0.1f), FColor::Green, false, 5.f);
			//DrawDebugSolidBox(GetWorld(), GetActorLocation(), FVector(0.1f, 0.1f, 0.1f), FColor::Yellow, false, 5.f);

			uint8 rayHits = 0;  //rot+,rot-,zoom+,zoom-

			if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 0, -1), ECameraDirectionRotationType::Model) * FMath::Abs((GetActorLocation() - position).Z) * 2, ObjectParams, QueryParams))
			{
				//FString LineTraceResult = FString::Printf(TEXT("FVector(0, 0, -1) > 0"));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, LineTraceResult);

				//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 0, -1), ECameraDirectionRotationType::Model) * FMath::Abs((GetActorLocation() - position).Z) * 2, FColor::Green, true, 1.f);
				//DrawDebugSolidBox(GetWorld(), OutHit.Location, FVector(0.1f, 0.1f, 0.1f), FColor::Blue, false, 5.f);

				rayHits = rayHits | 1 << 1;

			}

			if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 0, 1), ECameraDirectionRotationType::Model) * FMath::Abs((GetActorLocation() - position).Z) * 2, ObjectParams, QueryParams))
			{
				//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 0, 1), ECameraDirectionRotationType::Model) * FMath::Abs((GetActorLocation() - position).Z) * 2, FColor::Green, true, 1.f);
				//DrawDebugSolidBox(GetWorld(), OutHit.Location, FVector(0.1f, 0.1f, 0.1f), FColor::Blue, false, 5.f);

				//FString LineTraceResult = FString::Printf(TEXT("FVector(0, 0, 1) < 0"));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, LineTraceResult);
				

				rayHits = rayHits | 1;

			}

			FVector sidePositive = (position - GetActorLocation()).ProjectOnTo(FVector(0, 1, 0));

			if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 1, 0), ECameraDirectionRotationType::Model) * sidePositive.Size() * 5, ObjectParams, QueryParams))
			{
				//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, 1, 0), ECameraDirectionRotationType::Model) * sidePositive.Size(), FColor::Red, true, 1.f);
				//DrawDebugSolidBox(GetWorld(), GetActorLocation() + TransformByCameraRotation(FVector(0, 1, 0), ECameraDirectionRotationType::Model) * sidePositive.Size(), FVector(0.1f, 0.1f, 0.1f), FColor::Blue, false, 5.f);

				//FString LineTraceResult = FString::Printf(TEXT("FVector(0, 1, 0) > 0"));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, LineTraceResult);

				rayHits = rayHits | 1 << 2;
			}

			FVector sideNegative = (position - GetActorLocation()).ProjectOnTo(FVector(0, -1, 0));
			if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, -1, 0), ECameraDirectionRotationType::Model) * sideNegative.Size() * 5, ObjectParams, QueryParams))
			{
				//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + TransformByCameraRotation(FVector(0, -1, 0), ECameraDirectionRotationType::Model) * sideNegative.Size(), FColor::Green, true, 1.f);
				//DrawDebugSolidBox(GetWorld(), GetActorLocation() + TransformByCameraRotation(FVector(0, -1, 0), ECameraDirectionRotationType::Model) * sideNegative.Size() * 5, FVector(0.1f, 0.1f, 0.1f), FColor::Green, false, 5.f);

				//FString LineTraceResult = FString::Printf(TEXT("FVector(0, -1, 0) < 0"));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, LineTraceResult);
				
				rayHits = rayHits | 1 << 3;
			}

			FVector FinalPosition = position;
			FRotator FinalRotation = NextRotation;
			FRotator FinalLookAt = rotation;
			float FinalZoomDistance = NextZoomDistance;

			//Constraint

			//Collisions on zoom axis and zooming
			if (rayHits & 0x3 && !FMath::IsNearlyZero(ZoomDirection))
			{

				ZoomedOffsetFromIndicator.Normalize();
				FVector rotatedDirection = NextRotation.RotateVector(ZoomedOffsetFromIndicator * ZoomDistance);
				FVector position = Indicator->GetActorLocation() + rotatedDirection;

				FinalPosition = position;
				FinalRotation = NextRotation;
				FinalZoomDistance = ZoomDistance;

				FString ConstraintType = FString::Printf(TEXT("constraint ZOOM"));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, ConstraintType);
			}

			//Collision on Yaw rotation
			if (rayHits & 0xC && !FMath::IsNearlyZero(RotationDirection))
			{


				FinalRotation = CurrentRotation;
				float YawDiff = (NextRotation - CurrentRotation).Yaw;

				
				if (rayHits & 0x8 && FMath::IsNegativeFloat(YawDiff) && !FMath::IsNearlyZero(YawDiff))
				{
					FinalRotation = NextRotation;
				}
				
				if(rayHits & 0x4 && !FMath::IsNegativeFloat(YawDiff) && !FMath::IsNearlyZero(YawDiff))
				{
					FinalRotation = NextRotation;
				}
				

				ZoomedOffsetFromIndicator.Normalize();

				FVector rotatedDirection = FinalRotation.RotateVector(ZoomedOffsetFromIndicator * FinalZoomDistance);
				FVector RotatedPosition = Indicator->GetActorLocation() + rotatedDirection;

				FinalPosition = RotatedPosition;

				FVector direction = Indicator->GetActorLocation() - FinalPosition;
				direction.Normalize();
				FinalLookAt = direction.Rotation();

				/*FString RotationDirectionInformation = FString::Printf(TEXT("Hits %x"),rayHits );
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, RotationDirectionInformation);

				FString RotationInformation = FString::Printf(TEXT("NextRotation Yaw %f, CurrentRotation Yaw %f Difference Yaw %f Chosen Yaw %f"), NextRotation.Yaw, CurrentRotation.Yaw, YawDiff, FinalRotation.Yaw);
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, RotationInformation);

				FString ConstraintType = FString::Printf(TEXT("constraint ROTATION"));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, ConstraintType);*/
			}

			//

			CurrentRotation = FinalRotation;
			ZoomDistance = FinalZoomDistance;
			SetActorLocation(FinalPosition);

			SetActorRotation(FinalLookAt);
			GetController()->SetControlRotation(FinalLookAt);


		}
		else
		{
			//DrawDebugLine(GetWorld(), GetActorLocation(), position, FColor::Green, true, 5.f);
			
			CurrentRotation = NextRotation;
			ZoomDistance = NextZoomDistance;
			SetActorLocation(position);
			SetActorRotation(rotation);
			GetController()->SetControlRotation(rotation);
		}
	}

	
	//READ
	//This is a pretty horrible solution BUT its the least terrible one since mapping an action and a function for each key is even crappier
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
	ZoomDirection = _value;
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

void ACameraPawn::OnTogglePause()
{
	UGameplayStatics::SetGamePaused(GetWorld(), !UGameplayStatics::IsGamePaused(GetWorld()));
}

UPawnMovementComponent * ACameraPawn::GetMovementComponent() const
{
    return MovementComponent;
}

