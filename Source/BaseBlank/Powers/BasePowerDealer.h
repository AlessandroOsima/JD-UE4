

#pragma once

#include "GameFramework/Actor.h"
#include "BasePowerDealer.generated.h"

#define PowerDealerCollisionChannel ECollisionChannel::ECC_GameTraceChannel7

UCLASS()
class BASEBLANK_API ABasePowerDealer : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Components")
	class USphereComponent * SphereCollider;
	
public:	
	// Sets default values for this actor's properties
	ABasePowerDealer(const FObjectInitializer & PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool ApplyEffectOnInteractableObjectInsideCollider(TSubclassOf<UBaseEffect> Effect, bool RemoveOtherEffects = true, bool OverrideObjectLocation = false, FVector OverrideLocation = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool ApplyEffectOnInteractableObject(TSubclassOf<UBaseEffect> Effect, AActor * Actor);

	//Applies the effect to an actor if its an interactable object. It also spawns particle effects (depending on the type of the actor).
	//Returns if the actor is an interactable object and the spawned particle emitter component
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool OnActorCollision(const FHitResult & HitInfo, TSubclassOf<UBaseEffect> Effect, class UParticleSystem* InteractableFoundEmitterTemplate, class UParticleSystem* NoInteractableFoundEmitterTemplate, UParticleSystemComponent *& SpawnedParticleSystem, TEnumAsByte<ECollisionChannel> FloorChannel, FVector ParticleObjectScaleModifier, float TerrainSearchRaycastLenght = 500, bool RemoveOtherEffects = true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JD|Powers")
	float Speed;
};
