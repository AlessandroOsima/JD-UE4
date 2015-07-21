#include "BaseBlank.h"
#include "Global/BaseBlankGameMode.h"
#include "Global/GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
#include "BasePowerActor.h"


bool ABasePowerActor::CanUse_Implementation()
{
	return true;
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