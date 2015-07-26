#pragma once

#include "GameplayDebuggingHUDComponent.h"
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include "JDDebuggingHUDComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API AJDDebuggingHUDComponent : public AGameplayDebuggingHUDComponent
{
	GENERATED_BODY()

protected:
	virtual void DrawGameSpecificView(APlayerController* PC, class UGameplayDebuggingComponent *DebugComponent) override;
	virtual void GetKeyboardDesc(TArray<FDebugCategoryView>& Categories) override;
};
