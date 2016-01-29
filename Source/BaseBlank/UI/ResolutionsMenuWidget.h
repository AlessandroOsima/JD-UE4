

#pragma once

#include "UI/ListMenuWidget.h"
#include "ListMenuButton.h"
#include "ResolutionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UResolutionsMenuWidget : public UListMenuWidget
{
	GENERATED_BODY()

	//UPROPERTY(BlueprintReadWrite, Category="Menu")
	//TSubclassOf<UUserWidget> ButtonWidget;



protected:
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void SetButtonToReplicateAndEntries(TSubclassOf<UListMenuButton> ButtonWidgetClass, TArray<FIntPoint> Resolutions, UVerticalBox * FrameWidget);
	
};
