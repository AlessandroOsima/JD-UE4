

#pragma once

#include "Blueprint/UserWidget.h"
#include "ListMenuButton.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UListMenuButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Button")
	UButton * Button;

	UPROPERTY(BlueprintReadWrite, Category = "Button")
	UTextBlock * TextBlock;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FSlateColor SelectedColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FSlateColor UnSelectedColor = FColor::Blue;

	UButton * GetButton()
	{
		return Button;
	}

	UTextBlock * GetTextBlock()
	{
		return TextBlock;
	}
};
