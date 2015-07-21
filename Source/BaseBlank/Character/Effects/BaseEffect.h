#pragma once

#include "Object.h"
#include "BaseEffect.generated.h"

/**
 * 
 */

class ABaseCharacter;

UCLASS(BlueprintType, Blueprintable)
class BASEBLANK_API UBaseEffect : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void StartUse(ABaseCharacter * Character);

	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void Using(ABaseCharacter * Character, float DeltatTime);
	
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void EndUse(ABaseCharacter * Character);
	
};
