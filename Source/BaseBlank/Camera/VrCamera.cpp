

#include "BaseBlank.h"
#include "VrCamera.h"


// Sets default values
AVrCamera::AVrCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVrCamera::BeginPlay()
{
	Super::BeginPlay();
	
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

