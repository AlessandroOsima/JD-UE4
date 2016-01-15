

#include "BaseBlank.h"
#include "Runtime/Core/Public/Delegates/Delegate.h"
#include "ListMenuWidget.h"




void UListMenuWidget::UpdateHoverData()
{
	for (auto & WidgetInfo : ListMenuButtons)
	{
		if (WidgetInfo.Button->HasKeyboardFocus())
		{
			WidgetInfo.ButtonText->SetColorAndOpacity(SelectedColor);
		}
		else
		{
			WidgetInfo.ButtonText->SetColorAndOpacity(UnselectedColor);
		}
	}
}

void UListMenuWidget::InitButtonsAndCallbacks(const TArray<FListMenuButtonInfo> & MenuButtons, const FSlateColor & UnselectedColor, const FSlateColor & SelectedColor)
{
	ListMenuButtons = MenuButtons;
	this->SelectedColor = SelectedColor;
	this->UnselectedColor = UnselectedColor;

	for (auto & WidgetInfo : ListMenuButtons)
	{
		//NOTE: If this is added then the blueprint event will not be called
		//WidgetInfo.Button->OnClicked.AddDynamic(this, &UListMenuWidget::OnButtonClicked);
		WidgetInfo.Button->OnHovered.AddDynamic(this, &UListMenuWidget::OnButtonHover);
		WidgetInfo.Button->OnUnhovered.AddDynamic(this, &UListMenuWidget::OnButtonUnHover);
		//NOTE: Do NOT implement this as it messes up the delegates reception for button up/down needed to register a click
		//WidgetInfo.Button->OnPressed.AddDynamic(this, &UListMenuWidget::OnButtonPress);
		WidgetInfo.Button->OnReleased.AddDynamic(this, &UListMenuWidget::OnButtonReleased);
	}
}

//void UListMenuWidget::OnButtonClicked()
//{
//}

void UListMenuWidget::OnButtonHover()
{
	for (auto & WidgetInfo : ListMenuButtons)
	{
		if (WidgetInfo.Button->IsHovered())
		{
			APlayerController * controller = GetWorld()->GetFirstPlayerController();
			ensure(controller);

			FInputModeGameAndUI InputMode;
			//InputMode.SetLockMouseToViewport(bLockMouseToViewport);
			//InputMode.SetHideCursorDuringCapture(bHideCursorDuringCapture);
			WidgetInfo.ButtonText->SetColorAndOpacity(SelectedColor);
			InputMode.SetWidgetToFocus(WidgetInfo.Button->TakeWidget());
			controller->SetInputMode(InputMode);
		}
	}
}

void UListMenuWidget::OnButtonUnHover()
{
	for (auto & WidgetInfo : ListMenuButtons)
	{
		if (!WidgetInfo.Button->IsHovered())
		{
			WidgetInfo.ButtonText->SetColorAndOpacity(UnselectedColor);
		}
	}
}

//void UListMenuWidget::OnButtonPress()
//{
//	for (auto & WidgetInfo : ListMenuButtons)
//	{
//		if (WidgetInfo.Button->IsPressed())
//		{
//			APlayerController * controller = GetWorld()->GetFirstPlayerController();
//			ensure(controller);
//
//			FInputModeGameAndUI InputMode;
//			//InputMode.SetLockMouseToViewport(bLockMouseToViewport);
//			//InputMode.SetHideCursorDuringCapture(bHideCursorDuringCapture);
//			WidgetInfo.ButtonText->SetColorAndOpacity(SelectedColor);
//			InputMode.SetWidgetToFocus(WidgetInfo.Button->TakeWidget());
//			controller->SetInputMode(InputMode);
//		}
//	}
//}

void UListMenuWidget::OnButtonReleased()
{
	for (auto & WidgetInfo : ListMenuButtons)
	{
		if (!WidgetInfo.Button->IsPressed())
		{
			WidgetInfo.ButtonText->SetColorAndOpacity(UnselectedColor);
		}
	}
}

void UListMenuWidget::NativeDestruct()
{
	for (auto & WidgetInfo : ListMenuButtons)
	{
		WidgetInfo.Button->OnHovered.RemoveAll(this);
		WidgetInfo.Button->OnUnhovered.RemoveAll(this);
		WidgetInfo.Button->OnReleased.RemoveAll(this);
	}
	ListMenuButtons.Empty();
	Super::NativeDestruct();
}

