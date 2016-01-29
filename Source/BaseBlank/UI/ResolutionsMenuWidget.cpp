

#include "BaseBlank.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ResolutionsMenuWidget.h"




void UResolutionsMenuWidget::SetButtonToReplicateAndEntries(TSubclassOf<UListMenuButton> ButtonWidgetClass, TArray<FIntPoint> Resolutions, UVerticalBox * FrameWidget)
{
	ensure(FrameWidget);

	for (auto & resolution : Resolutions)
	{
		UListMenuButton * widget = CreateWidget<UListMenuButton>(UGameplayStatics::GetPlayerController(GetWorld(),0), ButtonWidgetClass);		
		//UTextBlock * textBlock = Cast<UTextBlock>(widget->GetChildAt(0));
		//ensureMsgf(textBlock, TEXT("We expect to have a text block as the button first child"));
		//widget->GetTextBlock()->SetText(FText::FromString(FString::Printf(TEXT("%dX%d"), resolution.X, resolution.Y)));
		UVerticalBoxSlot * slot = FrameWidget->AddChildToVerticalBox(widget);
		slot->SetHorizontalAlignment(HAlign_Fill);
		slot->SetVerticalAlignment(VAlign_Fill);
		slot->SetSize(ESlateSizeRule::Fill);
	}
}