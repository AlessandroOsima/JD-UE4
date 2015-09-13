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
	void StartUse(AActor * Owner);

	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void Using(AActor * Owner, float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent, Category = "JD|Powers")
	void EndUse(AActor * Owner);

	//Used to do active effects count with game mode
	//TODO: maybe should be automatic, but perf ??

	//Register this effect with the game mode. The player should not win/lose when a power effect is still active
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void RegisterToGameMode();

	//Unregister this effect with the game mode 
	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void UnregisterFromGameMode();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void RemoveAndUnregisterFromOwner(AActor * Owner);
	
};
