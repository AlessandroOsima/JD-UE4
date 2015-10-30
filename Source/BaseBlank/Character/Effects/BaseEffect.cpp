#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "Global/BaseBlankGameMode.h"
#include "Character/Components/EffectComponent.h"
#include "BaseEffect.h"

void UBaseEffect::StartUse_Implementation(AActor * Owner)
{
	//RegisterToGameMode();
}

void UBaseEffect::Using_Implementation(AActor * Owner, float DeltatTime)
{

}

void UBaseEffect::EndUse_Implementation(AActor * Owner)
{
	//UnregisterFromGameMode();
}

void UBaseEffect::RegisterToGameMode()
{
	UObject * outer = this->GetOuter();

	UWorld * World = outer->GetWorld();

	ensure(World);
	ABaseBlankGameMode * baseBlankGameMode = Cast<ABaseBlankGameMode>(World->GetAuthGameMode());

	ensureMsgf(baseBlankGameMode, TEXT("No valid game mode found"));
	baseBlankGameMode->AddActiveEffect(this);
}

void UBaseEffect::UnregisterFromGameMode()
{
	UObject * outer = this->GetOuter();

	UWorld * World = outer->GetWorld();

	ensure(World);
	ABaseBlankGameMode * baseBlankGameMode = Cast<ABaseBlankGameMode>(World->GetAuthGameMode());

	ensureMsgf(baseBlankGameMode, TEXT("No valid game mode found"));
	baseBlankGameMode->RemoveActiveEffect(this);
}

void UBaseEffect::RemoveAndUnregisterFromOwner(AActor * Owner)
{
	ensure(Owner);

	UPowerInteractionsComponent * cmp = Cast<UPowerInteractionsComponent>(Owner->GetComponentByClass(UPowerInteractionsComponent::StaticClass()));

	ensure(cmp);

	cmp->RemoveEffect(this);

	UnregisterFromGameMode();
}

