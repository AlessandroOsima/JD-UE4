
#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "EffectComponent.h"


void UPowerInteractionsComponent::AddEffect(UBaseEffect * effect)
{
	Effects.Add(effect);
	effect->StartUse(GetOwner());
}

void UPowerInteractionsComponent::RemoveEffect(UBaseEffect * effect)
{
	Effects.Remove(effect);
	effect->EndUse(GetOwner());
}

void UPowerInteractionsComponent::RemoveAllEffects()
{
	while (Effects.Num())
	{
		RemoveEffect(Effects.Last());
	}
}

void UPowerInteractionsComponent::AddShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower)
{
	ShieldedFromPowers.Add(shieldedPower);
}

void UPowerInteractionsComponent::RemoveShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower)
{
	ShieldedFromPowers.Remove(shieldedPower);
}

bool UPowerInteractionsComponent::IsShieldedFromPower(TSubclassOf<ABasePowerActor> shieldedPower)
{
	return ShieldedFromPowers.Contains(shieldedPower);
}

void UPowerInteractionsComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	for (auto effect : Effects)
	{
		effect->Using(GetOwner(), DeltaTime);
	}
}

