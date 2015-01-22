#pragma once

#include "Blueprint/UserWidget.h"
#include "UserWidget.h"
#include "PowerWidget.generated.h"


class ABasePowerActor;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BASEBLANK_API UPowerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Power Setup")
	void SetPowerOwner(class ABasePowerActor * _owner);

	UFUNCTION(BlueprintCallable, Category = "Power Setup")
	ABasePowerActor * GetPowerOwner();

public: 
	UFUNCTION(BlueprintCallable, Category = "Power Setup")
	void SetWidgetToNotifyOnCheck(UUserWidget * _toNotify);

	UFUNCTION(BlueprintCallable, Category = "UI Commands")
	void EnablePower(bool Enable);

	UFUNCTION(BlueprintCallable, Category = "UI Commands")
	void CheckPower(bool Check);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI Commands")
	void OnPowerEnable(bool Enable);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Commands")
	void OnPowerCheck(bool Check);
	
	UPROPERTY(BlueprintReadOnly)
    ABasePowerActor * Owner;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget * CheckedNotifyTarget;

	UPROPERTY(BlueprintReadWrite)
	UCheckBox * WidgetCheckBox;

};
