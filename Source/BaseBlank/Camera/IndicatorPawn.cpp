

#include "BaseBlank.h"
#include "Camera/Indicator/IndicatorTargetComponent.h"
#include "IndicatorPawn.h"


// Sets default values
AIndicatorPawn::AIndicatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIndicatorPawn::BeginPlay()
{
	Super::BeginPlay();

	FloatingPawn = (UFloatingPawnMovement *)GetComponentByClass(UFloatingPawnMovement::StaticClass());
	
	if (FloatingPawn)
	{
		NormalStateAcceleration = FloatingPawn->Acceleration;
	}

	ScaleToRestore = GetActorScale3D();
}

// Called every frame
void AIndicatorPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//The x-y position the indicator must move to
	FVector loc;

	if (State != EIndicatorTargetingState::NoTarget && State != EIndicatorTargetingState::HoverOnTarget)
	{
		//I'm using the Actor location in Z to have a common distance from ground for the raycast
		loc = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, GetActorLocation().Z);
	}
	else
	{
		loc = GetActorLocation();
	}

	//The hit info for the terrain collider
	FHitResult result;

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(GroundCollisionChannel);

	//Find the distance from the terrain
	if (GetWorld()->LineTraceSingleByObjectType(result, loc, loc + FVector(0, 0, -1) * GroundRaycastLenght, ObjectParams))
	{
		loc.Z = result.ImpactPoint.Z + GroundDistance;

		//DrawDebugSolidBox(GetWorld(), result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, true);
	}

	//DrawDebugSolidBox(GetWorld(), loc, FVector(5, 5, 5), FColor::Yellow, true);

	//The direction the indicator must move to reach the target
	FVector direction = loc - FVector(this->GetActorLocation().X, this->GetActorLocation().Y, loc.Z);

	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + direction * direction.Size(), FColor::Red);
	direction.Normalize();

	if (State != EIndicatorTargetingState::NoTarget && State != EIndicatorTargetingState::HoverOnTarget)
	{

		float distance = FVector::Dist(FVector(loc.X, loc.Y, loc.Z), FVector(this->GetActorLocation().X, this->GetActorLocation().Y, loc.Z));

		FString string = FString::Printf(TEXT("Target pos %s, Indicator pos %s, Distance %f"), *Target->GetActorLocation().ToCompactString(), *GetActorLocation().ToCompactString(), distance);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);

		if (State == EIndicatorTargetingState::OnTarget || distance < Tolerance)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Indicator in Tolerance range"));

			//Set the actor location

			State = EIndicatorTargetingState::OnTarget;
			SetActorLocation(loc);
			OnIndicatorStateChanged(State);
		}
		else if (State == EIndicatorTargetingState::MoveToTarget)//Move to target if outside tolerance range and target is selected
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Indicator out of Tolerance range"));

			float index = (distance / MaxDistance) - (Tolerance / MaxDistance);
			float acceleration = AccelerationOverDistance->GetFloatValue(index);

			if (EnableScaleTransform)
			{
				float XYScale = FMath::Lerp(TargetScale.X, ScaleToRestore.X, index);
				SetActorScale3D(FVector(XYScale, XYScale, ScaleToRestore.Z));
			}

			FString string = FString::Printf(TEXT("Acceleration is %f, normal dist is %f, dist is %f, max dist is %f"), acceleration, distance / MaxDistance, distance, MaxDistance);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);

			//FString string = FString::Printf(TEXT("Acceleration is %f"), acceleration);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);

			if (FloatingPawn)
			{
				FloatingPawn->Acceleration = acceleration;
			}

			this->AddMovementInput(direction);
		}
	}

}

// Called to bind functionality to input
void AIndicatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AIndicatorPawn::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	Super::ReceiveActorBeginOverlap(OtherActor);
}

FORCEINLINE EIndicatorTargetingState AIndicatorPawn::GetIndicatorState()
{
	return State;
}

void AIndicatorPawn::SetTarget(AActor * Target)
{
	ensure(Target);

	this->Target = Target;

	//If we have a target to follow we don't need the movement component
	//GetMovementComponent()->Activate(false);

	State = EIndicatorTargetingState::MoveToTarget;
	MaxDistance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
	OnIndicatorStateChanged(State);

	APawn * pawn = Cast<APawn>(Target);

	if (pawn)
	{
		AController * controller = pawn->GetController();

		if (controller)
		{
			UIndicatorTargetComponent * cmp = (UIndicatorTargetComponent *)controller->GetComponentByClass(UIndicatorTargetComponent::StaticClass());
		    
			if (cmp)
			{
				cmp->SetIndicator(this);
			}
		}
	}
}

void AIndicatorPawn::UnsetTarget()
{
	Target = nullptr;

	//Reenable standard movement
	//GetMovementComponent()->Activate(true);

	FloatingPawn->Acceleration = NormalStateAcceleration;
	State = EIndicatorTargetingState::NoTarget;
	OnIndicatorStateChanged(State);

	APawn * pawn = Cast<APawn>(Target);

	if (pawn)
	{
		AController * controller = pawn->GetController();

		if (controller)
		{
			UIndicatorTargetComponent * cmp = (UIndicatorTargetComponent *)controller->GetComponentByClass(UIndicatorTargetComponent::StaticClass());

			if (cmp)
			{
				cmp->SetIndicator(nullptr);
			}
		}
	}

	SetActorScale3D(ScaleToRestore);
	EnableScaleTransform = false;

}

AActor * AIndicatorPawn::GetTarget()
{
	return Target;
}

bool AIndicatorPawn::HasTarget()
{
	return Target != nullptr;
}

void AIndicatorPawn::SetState(EIndicatorTargetingState State)
{
	this->State = State;
	OnIndicatorStateChanged(this->State);
}

void AIndicatorPawn::TargetStartInteraction(UWaypointInteractionComponent * Interaction)
{
	ensure(Interaction);

	OnTargetStartInteraction(Interaction);
}

void AIndicatorPawn::TargetEndInteraction(UWaypointInteractionComponent * Interaction)
{
	ensure(Interaction);

	OnTargetEndInteraction(Interaction);
}

void AIndicatorPawn::ScaleToSphereCollider(AActor * Actor)
{
	ensure(Actor);

	USphereComponent * sphere = (USphereComponent *)Actor->GetComponentByClass(USphereComponent::StaticClass());
	
	if (sphere)
	{
		float ray = sphere->GetScaledSphereRadius();

		if (RayToScale)
		{
			float scale = RayToScale->GetFloatValue(ray);

			//SetActorScale3D(FVector(scale, scale, ScaleToRestore.Z));

			TargetScale = FVector(scale, scale, ScaleToRestore.Z);

			EnableScaleTransform = true;
		}
	}
}

void AIndicatorPawn::ReceiveHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

}
