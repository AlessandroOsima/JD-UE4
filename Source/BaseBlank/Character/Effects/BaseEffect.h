#pragma once

#include "Object.h"
#include "BaseEffect.generated.h"

/**
 * 
 */

class ABaseCharacter;


//The outer of this class must be an actor (needed for the GetWorld in the Register* functions)
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

	//Register this effect with the game mode. The player should not win/lose when a power effect is still active
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void RegisterToGameMode();

	//Unregister this effect with the game mode 
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void UnregisterFromGameMode();
	
};
