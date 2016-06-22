
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

bool UPowerInteractionsComponent::HasEffectOfClass(TSubclassOf<UBaseEffect> Class, bool AlsoChild, bool AlsoParent) const
{
	bool result = false;

	for (auto effect : Effects)
	{

		result = result || Class == effect->GetClass();

		if (AlsoChild)
		{
			result = result || Class->IsChildOf(effect->GetClass());
		}

		if (AlsoParent)
		{
			result = result || effect->GetClass()->IsChildOf(Class);
		}

	}

	return result;
}

bool UPowerInteractionsComponent::HasEffects() const
{
	return Effects.Num() > 0;
}

UBaseEffect * UPowerInteractionsComponent::HigherPriorityEffect() const
{
	if (Effects.Num() == 0)
		return nullptr;

	UBaseEffect * highestPrio = Effects[0];
	int32 prioVal = Effects[0]->Priority;

	for (int i = 1; i < Effects.Num(); i++)
	{
		if (Effects[i]->Priority > prioVal)
		{
			highestPrio = Effects[i];
			prioVal = Effects[i]->Priority;
		}
	}

	return highestPrio;
}

bool UPowerInteractionsComponent::HigherPriorityEffectIsOfClass(TSubclassOf<UBaseEffect> Class) const
{
	auto effect = HigherPriorityEffect();
	bool isOfClass = false;

	if (effect && effect->GetClass() == Class)
	{
		isOfClass = true;
	}

	return isOfClass;
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
	for (int i = 0; i < Effects.Num(); i++)
	{
		Effects[i]->Using(GetOwner(), DeltaTime);
	}
}

