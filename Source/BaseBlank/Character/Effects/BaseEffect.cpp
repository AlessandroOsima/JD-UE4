#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "Global/BaseBlankGameMode.h"
#include "BaseEffect.h"



void UBaseEffect::StartUse_Implementation(ABaseCharacter * Character)
{
	//RegisterToGameMode();
}

void UBaseEffect::Using_Implementation(ABaseCharacter * Character, float DeltatTime)
{

}

void UBaseEffect::EndUse_Implementation(ABaseCharacter * Character)
{
	//UnregisterFromGameMode()
}

void UBaseEffect::RegisterToGameMode()
{

	UObject * outer = this->GetOuter();

	UWorld * World = outer->GetWorld();

	ensure(World);
	ABaseBlankGameMode * baseBlankGameMode = Cast<ABaseBlankGameMode>(World->GetAuthGameMode());

	ensureMsg(baseBlankGameMode, TEXT("No valid game mode found"));
	baseBlankGameMode->AddActiveEffect(this);
}

void UBaseEffect::UnregisterFromGameMode()
{
	UObject * outer = this->GetOuter();

	UWorld * World = outer->GetWorld();

	ensure(World);
	ABaseBlankGameMode * baseBlankGameMode = Cast<ABaseBlankGameMode>(World->GetAuthGameMode());

	ensureMsg(baseBlankGameMode, TEXT("No valid game mode found"));
	baseBlankGameMode->RemoveActiveEffect(this);
}
