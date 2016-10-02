#include "BaseBlank.h"
#include "Global/BaseBlankGameMode.h"
#include "Global/GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
#include "BasePowerDealer.h"
#include "Character/BaseCharacter.h"
#include "Character/Effects/BaseEffect.h"
#include "BasePowerActor.h"


bool ABasePowerActor::CanUse_Implementation()
{
	return HasEnoughSoulsToSpend();
}

void ABasePowerActor::Use_Implementation()
{

}

void ABasePowerActor::Selecting_Implementation()
{

}

void ABasePowerActor::UnSelecting_Implementation()
{
}

ABasePowerActor::ABasePowerActor(const FObjectInitializer & PCIP) : Super(PCIP), CanHaveChainedEffects(false)
{
	SphereCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereCollider"));
	SphereCollider->SetSphereRadius(100);
}

void ABasePowerActor::SpendSouls()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsgf(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsgf(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

	cmp->UseSoulsAmount(SoulsCost);
	
}

bool ABasePowerActor::CanSpendWithoutLosing()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsgf(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsgf(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

	if (cmp->CanSpendSouls(SoulsCost))
	{
		return true;
	}

	return false;
}

bool ABasePowerActor::ApplyEffectOnCharacter(TSubclassOf<UBaseEffect> Effect, ABaseCharacter * BaseCharacter)
{
	ensure(Effect);

	ensure(BaseCharacter);


	if (!BaseCharacter->PowerInteractionsComponent->IsShieldedFromPower(this->GetClass()))
	{
		UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)BaseCharacter, Effect));

		BaseCharacter->PowerInteractionsComponent->AddEffect(created);

		return true;
	}

	return false;
}

bool ABasePowerActor::ApplyEffectOnInteractableObject(TSubclassOf<UBaseEffect> Effect, bool RemoveOtherEffects, bool OverrideObjectLocation, FVector OverrideLocation)
{


	FVector location = OverrideObjectLocation ? SphereCollider->GetComponentLocation() : OverrideLocation;

	//TArray<FOverlapResult> overlaps;
	/*SphereCollider->ComponentOverlapMulti(overlaps,
		this->GetWorld(),
		location,
		SphereCollider->GetComponentRotation(), ECollisionChannel::ECC_Pawn,
		FComponentQueryParams());*/

	TArray<AActor * > overlappingActors;
	SphereCollider->GetOverlappingActors(overlappingActors);

	bool result = false;

	if (overlappingActors.Num() > 0)
	{
		for (int i = 0; i < overlappingActors.Num(); i++)
		{
			AActor * hitTarget = overlappingActors[i];
    
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

void ABasePowerActor::ApplyEffectBasedOnPowerStart(TSubclassOf<UBaseEffect> Effect, TSubclassOf<ABasePowerDealer> Dealer, FTransform NewOverrideTransform, bool RemoveOtherEffects /*= true*/, bool OverrideTransform /*= false*/)
{
	SpendSouls();

	if (PowerStart == EPowerStart::Immediate)
	{
		ApplyEffectOnInteractableObject(Effect, RemoveOtherEffects);
	}
	else
	{
		FTransform TargetTransform = GetActorTransform();

		if (OverrideTransform)
		{
			TargetTransform = NewOverrideTransform;
		}

		GetWorld()->SpawnActor<ABasePowerDealer>(*Dealer, TargetTransform, FActorSpawnParameters());
	}
}

bool ABasePowerActor::CanBeUsedOnThisCharacter(ABaseCharacter * BaseCharacter)
{
	ensure(BaseCharacter);

	return !BaseCharacter->PowerInteractionsComponent->IsShieldedFromPower(this->GetClass());
}

bool ABasePowerActor::CanBeUsedOnThisInteractable(UPowerInteractionsComponent * InteractableObject)
{
	return !InteractableObject->IsShieldedFromPower(this->GetClass());
}

bool ABasePowerActor::CanBeUsedOnThisCharacterWithoutLosing(ABaseCharacter * BaseCharacter)
{
	ensure(BaseCharacter);

	return CanBeUsedOnThisCharacter(BaseCharacter) && CanSpendWithoutLosing();
}

bool ABasePowerActor::HasEnoughSoulsToSpend()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsgf(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsgf(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

	if (cmp->GetSoulsAmount() - SoulsCost >= 0)
	{
		return true;
	}

	return false;
}

bool ABasePowerActor::CanBeUsedOnValidTarget()
{
	if (HasEnoughSoulsToSpend())
	{
		TArray<FOverlapResult> overlaps;

		SphereCollider->ComponentOverlapMulti(overlaps,
			this->GetWorld(),
			SphereCollider->GetComponentLocation(),
			SphereCollider->GetComponentRotation(), ECollisionChannel::ECC_Pawn,
			FComponentQueryParams());

		if (overlaps.Num() > 0)
		{
			for (int i = 0; i < overlaps.Num(); i++)
			{
				UActorComponent * cmp = overlaps[i].GetActor()->GetComponentByClass(UPowerInteractionsComponent::StaticClass());

				if (cmp)
				{
					UPowerInteractionsComponent * powerInteraction = Cast<UPowerInteractionsComponent>(cmp);

					if (powerInteraction)
					{
						if (CanHaveChainedEffects)
						{
							return CanBeUsedOnThisInteractable(powerInteraction);
						}
						else
						{
							//If we have a hit and we have enough souls we still have to check if the character is not shielded and if no effect are already active
							return powerInteraction->Effects.Num() == 0 && CanBeUsedOnThisInteractable(powerInteraction);
						}
					}
				}
			}
		}

		return true;
	}

	//If no souls the power cannot be used
	return false;
}

bool ABasePowerActor::IsValidTarget(AActor * target)
{
	ensure(target);

	if (target->GetComponentByClass(UPowerInteractionsComponent::StaticClass()))
	{
		return true;
	}

	return false;
}

