

#pragma once

#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "ListMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FListMenuButtonInfo
{
	GENERATED_USTRUCT_BODY()

public:
	//A button composing the menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	UButton * Button;
	//The text of the buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	UTextBlock * ButtonText;
};

/**
 * Helpers for a list of buttons that change color based if they are hovered or pressed
 * Should be inherited in blueprint to set the behaviour of single buttons when pressed
 */
UCLASS()
class BASEBLANK_API UListMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void UpdateHoverData();

	/**
	* Register listeners on the buttons and the colors the menu buttons should have when selected or not
	*
	* @param MenuButtons The buttons composing the menu
	* @param UnselectedColor The color the buttons text should have when unselected
	* @param SelectedColor   The color the buttons text should have when selected
	*/
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void InitButtonsAndCallbacks(const TArray<FListMenuButtonInfo> & MenuButtons, const FSlateColor & UnselectedColor, const FSlateColor & SelectedColor);

	//---------------------NATIVE DELEGATES ON MENU BUTTONS-----------------------------------
	/*
	NOTE: If this is added then the blueprint event will not be called
	UFUNCTION(Category = "Menu C++ Bindings")
	void OnButtonClicked();
	*/
	UFUNCTION(Category = "Menu C++ Bindings")
	void OnButtonHover();
	UFUNCTION(Category = "Menu C++ Bindings")
	void OnButtonUnHover();
	/* NOTE: Do NOT implement this as it messes up the delegates reception for button up/down needed to register a click
	UFUNCTION(Category = "Menu C++ Bindings")
	void OnButtonPress();*/
	UFUNCTION(Category = "Menu C++ Bindings")
	void OnButtonReleased();
	//---------------------------------------------------------------------------------------

	//Unregister the delegate on the menu buttons
	virtual void NativeDestruct() override;

private:
	FSlateColor UnselectedColor;
	FSlateColor SelectedColor;
	TArray<FListMenuButtonInfo> ListMenuButtons;

};
