
#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "EffectComponent.h"


void UEffectComponent::AddEffect(UBaseEffect * effect)
{
	Effects.Add(effect);
	effect->StartUse(Cast<ABaseCharacter>(GetOwner()));
}

void UEffectComponent::RemoveEffect(UBaseEffect * effect)
{
	Effects.Remove(effect);
	effect->EndUse(Cast<ABaseCharacter>(GetOwner()));
}

void UEffectComponent::RemoveAllEffects()
{
	while (Effects.Num())
	{
		RemoveEffect(Effects.Last());
	}
}

void UEffectComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	for (auto effect : Effects)
	{
		effect->Using(Cast<ABaseCharacter>(GetOwner()), DeltaTime);
	}
}

