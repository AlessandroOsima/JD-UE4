

#include "BaseBlank.h"
#include "VrCamera.h"


// Sets default values
AVrCamera::AVrCamera(const class FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerRaycaster = PCIP.CreateDefaultSubobject<UPowerRayCasterComponent>(this, TEXT("PowerRaycaster"));
	PowerRaycaster->PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVrCamera::BeginPlay()
{
	Super::BeginPlay();

	PowerRaycaster->RegisterComponent();
}

// Called every frame
void AVrCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AVrCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool AVrCamera::DoTargetRaycast(FVector StartLocation, FVector EndLocation, TEnumAsByte<ECollisionChannel> FloorChannel)
{
	bLastPositionIsValid = false;

	FCollisionObjectQueryParams CollisionQueryParams;

	CollisionQueryParams.AddObjectTypesToQuery(FloorChannel);

	FHitResult OutHit;
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, StartLocation, EndLocation, CollisionQueryParams))
	{
		DrawDebugLine(GetWorld(), StartLocation, OutHit.Location, FColor::Blue, false, -1.0f, 0, 1);
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 100, 12, FColor::Red);

		bLastPositionIsValid = true;
		LastValidPosition = OutHit.ImpactPoint;

		PowerRaycaster->SetActivePowerPosition(OutHit.ImpactPoint);

		//UE_LOG(LogTemp, Log, TEXT("Name %s"), *OutHit.Actor->GetName());

		return true;
	}

	
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 1);

	return false;
}

void AVrCamera::TeleportToLastValidPosition()
{
	if (bLastPositionIsValid)
	{
		this->SetActorLocation(FVector(LastValidPosition.X, LastValidPosition.Y, GetActorLocation().Z));
	}
}

