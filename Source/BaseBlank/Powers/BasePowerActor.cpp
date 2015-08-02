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


	if (!BaseCharacter->IsShieldedFromPower(this->GetClass()))
	{
		UBaseEffect * created = Cast<UBaseEffect>(NewObject<UObject>((UObject*)BaseCharacter, Effect));

		BaseCharacter->EffectComponent->AddEffect(created);

		return true;
	}

	return false;
}

bool ABasePowerActor::CanBeUsedOnThisCharacter(ABaseCharacter * BaseCharacter)
{
	ensure(BaseCharacter);

	return !BaseCharacter->IsShieldedFromPower(this->GetClass());
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

