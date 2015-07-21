#pragma once

#include "Character/Components/BaseCharacterComponent.h"
#include "Character/Effects/BaseEffect.h"
#include "EffectComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UEffectComponent : public UBaseCharacterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="JD|Effect Component") 
	TArray<UBaseEffect *> Effects;

	UFUNCTION(BlueprintCallable, Category = "JD|Effect Component")
	void AddEffect(UBaseEffect * effect);

	UFUNCTION(BlueprintCallable, Category = "JD|Effect Component")
	void RemoveEffect(UBaseEffect * effect);

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


};
