

#include "BaseBlank.h"
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
	
}

// Called every frame
void AIndicatorPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AIndicatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

