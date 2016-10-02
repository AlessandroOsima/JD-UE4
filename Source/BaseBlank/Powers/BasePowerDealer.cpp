

#include "BaseBlank.h"
#include "Character/Effects/BaseEffect.h"
#include "Character/Components/EffectComponent.h"
#include "Global/JDBlueprintFunctionLibrary.h"
#include "BasePowerDealer.h"


// Sets default values
ABasePowerDealer::ABasePowerDealer(const FObjectInitializer & PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
	SphereCollider->SetCollisionObjectType(PowerDealerCollisionChannel);
}

// Called when the game starts or when spawned
void ABasePowerDealer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePowerDealer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*FVector NewLocation = GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);*/

}

bool ABasePowerDealer::ApplyEffectOnInteractableObjectInsideCollider(TSubclassOf<UBaseEffect> Effect, bool RemoveOtherEffects /*= true*/, bool OverrideObjectLocation /*= false*/, FVector OverrideLocation /*= FVector::ZeroVector*/)
{
	TArray<FOverlapResult> overlaps;

	FVector location = OverrideObjectLocation ? SphereCollider->GetComponentLocation() : OverrideLocation;

	SphereCollider->ComponentOverlapMulti(overlaps,
		this->GetWorld(),
		location,
		SphereCollider->GetComponentRotation(), ECollisionChannel::ECC_Pawn,
		FComponentQueryParams());

	bool result = false;

	if (overlaps.Num() > 0)
	{
		for (int i = 0; i < overlaps.Num(); i++)
		{
			
			UE_LOG(LogTemp, Log, TEXT("Name %s with actor %s"), *this->GetName(), *overlaps[i].GetActor()->GetName());

			//TODO: Handle with other actors than base character
			AActor * hitTarget = overlaps[i].GetActor();

			if (!hitTarget)
			{
				result = result | false;
				continue;
			}

			UPowerInteractionsComponent * cmp = Cast<UPowerInteractionsComponent>(hitTarget->GetComponentByClass(UPowerInteractionsComponent::StaticClass()));
			if (hitTarget && cmp)
			{
				UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)hitTarget, Effect));
				cmp->RemoveAllEffects();
				cmp->AddEffect(created);
				result = result | true;
			}
		}
	}

	return result;
}

bool ABasePowerDealer::ApplyEffectOnInteractableObject(TSubclassOf<UBaseEffect> Effect, AActor * Actor)
{
	ensure(Actor);

	UPowerInteractionsComponent * cmp = Cast<UPowerInteractionsComponent>(Actor->GetComponentByClass(UPowerInteractionsComponent::StaticClass()));
	if (Actor && cmp)
	{
		UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)Actor, Effect));
		cmp->RemoveAllEffects();
		cmp->AddEffect(created);
		return true;
	}

	return false;
}

bool ABasePowerDealer::OnActorCollision(const FHitResult & HitInfo, TSubclassOf<UBaseEffect> Effect, class UParticleSystem* InteractableFoundEmitterTemplate, class UParticleSystem* NoInteractableFoundEmitterTemplate, UParticleSystemComponent *& SpawnedParticleSystem, TEnumAsByte<ECollisionChannel> FloorChannel, FVector ParticleObjectScaleModifier, float TerrainSearchRaycastLenght, bool RemoveOtherEffects /*= true*/)
{
	if (UJDBlueprintFunctionLibrary::IsAnInteractableObject(HitInfo.GetActor()))
	{
		FVector TerrainLocation;
		
		if (UJDBlueprintFunctionLibrary::DoTerrainRaycast(this, HitInfo.Location, HitInfo.Location + FVector(0, 0, -TerrainSearchRaycastLenght), FloorChannel, TerrainLocation))
		{
			SpawnedParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InteractableFoundEmitterTemplate, TerrainLocation);
			SpawnedParticleSystem->SetWorldScale3D(ParticleObjectScaleModifier);

		}
		
		SpawnedParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InteractableFoundEmitterTemplate, TerrainLocation);
		SpawnedParticleSystem->SetWorldScale3D(ParticleObjectScaleModifier);

		return true;
	}

	SpawnedParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NoInteractableFoundEmitterTemplate, HitInfo.Location);
	SpawnedParticleSystem->SetWorldScale3D(ParticleObjectScaleModifier);

	return false;
}
