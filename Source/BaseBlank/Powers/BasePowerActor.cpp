#include "BaseBlank.h"
#include "Global/BaseBlankGameMode.h"
#include "Global/GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
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
	BoxCollider = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollider"));
	BoxCollider->SetBoxExtent(FVector(1, 1, 1), true);
}

void ABasePowerActor::SpendSouls()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsg(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsg(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

	cmp->UseSoulsAmount(SoulsCost);
	
}

bool ABasePowerActor::CanSpendWithoutLosing()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsg(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsg(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

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

bool ABasePowerActor::ApplyEffectOnInteractableObject(TSubclassOf<UBaseEffect> Effect)
{
	TArray<FOverlapResult> overlaps;

	BoxCollider->ComponentOverlapMulti(overlaps,
		this->GetWorld(),
		BoxCollider->GetComponentLocation(),
		BoxCollider->GetComponentRotation(), ECollisionChannel::ECC_Pawn,
		FComponentQueryParams());

	bool result = false;

	if (overlaps.Num() > 0)
	{
		for (int i = 0; i < overlaps.Num(); i++)
		{
			//TODO: Handle with other actors than base character
			AActor * hitTarget = overlaps[i].GetActor();
			UPowerInteractionsComponent * cmp = Cast<UPowerInteractionsComponent>(hitTarget->GetComponentByClass(UPowerInteractionsComponent::StaticClass()));
			if (hitTarget && cmp)
			{
				UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)hitTarget, Effect));
				cmp->AddEffect(created);
				result || true;
			}
		}
	}

	return result;
}

bool ABasePowerActor::CanBeUsedOnThisCharacter(ABaseCharacter * BaseCharacter)
{
	ensure(BaseCharacter);

	return !BaseCharacter->PowerInteractionsComponent->IsShieldedFromPower(this->GetClass());
}

bool ABasePowerActor::CanBeUsedOnThisCharacterWithoutLosing(ABaseCharacter * BaseCharacter)
{
	ensure(BaseCharacter);

	return CanBeUsedOnThisCharacter(BaseCharacter) && CanSpendWithoutLosing();
}

bool ABasePowerActor::HasEnoughSoulsToSpend()
{
	ABaseBlankGameMode * bsGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
	ensureMsg(bsGameMode != nullptr, TEXT("Unable to cast Game Mode to ABaseBlankGameMode"));

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(bsGameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
	ensureMsg(bsGameMode != nullptr, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

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

		BoxCollider->ComponentOverlapMulti(overlaps,
			this->GetWorld(),
			BoxCollider->GetComponentLocation(),
			BoxCollider->GetComponentRotation(), ECollisionChannel::ECC_Pawn,
			FComponentQueryParams());

		if (overlaps.Num() > 0)
		{
			for (int i = 0; i < overlaps.Num(); i++)
			{
				//TODO: Handle with other actors than base character
				ABaseCharacter * hitTarget = Cast<ABaseCharacter>(overlaps[i].GetActor());

				if (hitTarget)
				{
					if (CanHaveChainedEffects)
					{
						return CanBeUsedOnThisCharacter(hitTarget);
					}
					else
					{
						//If we have a hit and we have enough souls we still have to check if the character is not shielded and if no effect are already active
						return hitTarget->PowerInteractionsComponent->Effects.Num() == 0 && CanBeUsedOnThisCharacter(hitTarget);
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

