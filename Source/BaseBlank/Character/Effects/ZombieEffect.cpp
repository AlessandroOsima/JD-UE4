

#include "BaseBlank.h"
#include "ZombieEffect.h"
#include "Character/BaseCharacter.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "NPCController/NPCController.h"
#include "AI/NavigationSystemHelpers.h"
#include "VisualLogger/VisualLogger.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(ZombieEffect);

void UZombieEffect::StartUse_Implementation(AActor * Owner)
{
	ensure(BHTToPushOnCharacter);
	ensure(SpeedOverTime);
	ensure(EffectToApply);
	ensure(ZombieMeshMaterial);

	EffectTime = 0;

	this->Owner = Owner;

	ABaseCharacter * bChr = Cast<ABaseCharacter>(Owner);

	if (bChr)
	{
		UCharacterMovementComponent * cmp = Cast<UCharacterMovementComponent>(bChr->GetMovementComponent());
		if (cmp)
		{
			PrevMaxWalkSpeed = cmp->MaxWalkSpeed;
		}

		ANPCController * npcCtrl = Cast<ANPCController>(bChr->GetController());

		if (npcCtrl)
		{
			npcCtrl->GetPathFollowingComponent()->AbortMove(TEXT("New Effect Applied"));
			npcCtrl->PushNewBHTAsset(BHTToPushOnCharacter);
			RegisterToGameMode();

			
			UCrowdFollowingComponent * ccmp = Cast<UCrowdFollowingComponent>(npcCtrl->GetPathFollowingComponent());
			ccmp->SetAvoidanceGroup(ZombieAvoidanceGroup);
			ccmp->SetGroupsToAvoid(ZombieAvoidanceGroup);
			ccmp->SetGroupsToIgnore(CharacterAvoidanceGroup);
		}

		bChr->GetMesh()->CreateDynamicMaterialInstance(0, ZombieMeshMaterial);

		bChr->OnActorBeginOverlap.AddDynamic(this, &UZombieEffect::OnActorBeginOverlap);
		bChr->OnActorHit.AddDynamic(this, &UZombieEffect::OnActorCollisionHit);
	}
}

void UZombieEffect::Using_Implementation(AActor * Owner, float DeltaTime)
{
	EffectTime += DeltaTime;

	ABaseCharacter * bChr = Cast<ABaseCharacter>(Owner);

	if (bChr)
	{
		float maxWalkSpeed = SpeedOverTime->GetFloatValue(EffectTime);

		UCharacterMovementComponent * cmp = Cast<UCharacterMovementComponent>(bChr->GetMovementComponent());
		if (cmp)
		{
			cmp->MaxWalkSpeed = maxWalkSpeed;
			//FString data = FString::Printf(TEXT("Max walk speed %f, speed %f"), maxWalkSpeed, cmp->Velocity.Size());
			//DrawDebugString(bChr->GetWorld(), bChr->GetActorLocation(), data, nullptr, FColor::White, 0.0f);
		}
	}
}

void UZombieEffect::EndUse_Implementation(AActor * Owner)
{
	UnregisterFromGameMode();

	EffectTime = 0;

	ABaseCharacter * bChr = Cast<ABaseCharacter>(Owner);

	if (bChr)
	{
		UCharacterMovementComponent * cmp = Cast<UCharacterMovementComponent>(bChr->GetMovementComponent());
		if (cmp)
		{
			cmp->MaxWalkSpeed = PrevMaxWalkSpeed;

			cmp->SetAvoidanceGroup(CharacterAvoidanceGroup);
			cmp->SetGroupsToIgnore(CharacterAvoidanceGroup);
			UE_VLOG_LOCATION(Owner, ZombieEffect, Log, bChr->GetActorLocation(), 10, FColor::Green, TEXT("Speed %d"), bChr->GetVelocity().Size());
		}

		ANPCController * npcCtrl = Cast<ANPCController>(bChr->GetController());

		if (npcCtrl)
		{
			npcCtrl->PopBHTAsset();
		}


		bChr->OnActorBeginOverlap.RemoveDynamic(this, &UZombieEffect::OnActorBeginOverlap);
		bChr->OnActorHit.RemoveDynamic(this, &UZombieEffect::OnActorCollisionHit);
		//bChr->PowerEffectsCollider->OnComponentBeginOverlap.Remove()
	}

	this->Owner = nullptr;
}

void UZombieEffect::OnActorCollisionHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	if (!OtherActor)
	{
		return;
	}

	//FString string = FString::Printf(TEXT("Actor %s collision with Actor %s"), *SelfActor->GetName(), *OtherActor->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);

	UE_VLOG_LOCATION(Owner, ZombieEffect, Log, SelfActor->GetActorLocation(), 10, FColor::Green, TEXT("Zombie Effect Collision Self"));
	UE_VLOG_LOCATION(Owner, ZombieEffect, Log, OtherActor->GetActorLocation(), 10, FColor::Green, TEXT("Zombie Effect Collision Other"));


	if (OtherActor && OtherActor != Owner)
	{
		UPowerInteractionsComponent * pCmp = (UPowerInteractionsComponent*)OtherActor->GetComponentByClass(UPowerInteractionsComponent::StaticClass());

		if (pCmp && !pCmp->HasEffectOfClass(UZombieEffect::StaticClass()))
		{
			UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)Owner, EffectToApply));
			pCmp->RemoveAllEffects();
			pCmp->AddEffect(created);
		}

	}
}

void UZombieEffect::OnActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor && OtherActor != Owner)
	{
		UPowerInteractionsComponent * pCmp = (UPowerInteractionsComponent*)OtherActor->GetComponentByClass(UPowerInteractionsComponent::StaticClass());

		if (pCmp && !pCmp->HasEffectOfClass(UZombieEffect::StaticClass()))
		{
			UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)Owner, EffectToApply));
			pCmp->RemoveAllEffects();
			pCmp->AddEffect(created);
		}

	}
}

