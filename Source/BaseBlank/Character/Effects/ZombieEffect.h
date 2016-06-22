#pragma once

#include "Character/Effects/BaseEffect.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ZombieEffect.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ZombieEffect, Log, All);
/**
 * 
 */
UCLASS()
class BASEBLANK_API UZombieEffect : public UBaseEffect
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void StartUse(AActor * Owner);

	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void Using(AActor * Owner, float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void EndUse(AActor * Owner);
	
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UBehaviorTree * BHTToPushOnCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UCurveFloat * SpeedOverTime;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<UZombieEffect>  EffectToApply;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UMaterial * ZombieMeshMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	int32 ZombieAvoidanceGroup = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	int32 CharacterAvoidanceGroup = 1;

	UFUNCTION(Category = "JD|Collision")
	void OnActorCollisionHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(Category = "JD|Collision")
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
private:
	float EffectTime = 0;
	float PrevMaxWalkSpeed = 0;
	UMaterial * NormalMaterial;
	AActor * Owner = nullptr;
};
