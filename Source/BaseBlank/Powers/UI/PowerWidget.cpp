#include "BaseBlank.h"
#include "PowerWidget.h"
#include "Powers/BasePowerActor.h"

void UPowerWidget::SetPowerOwner(class ABasePowerActor * _owner)
{
	Owner = _owner;
}

void UPowerWidget::SetWidgetToNotifyOnCheck(UUserWidget * _toNotify)
{
	CheckedNotifyTarget = _toNotify;
}

ABasePowerActor * UPowerWidget::GetPowerOwner()
{
	return Owner;
}

void UPowerWidget::EnablePower(bool Enable)
{
	this->OnPowerEnable(Enable);
}

void UPowerWidget::CheckPower(bool Check)
{
	this->OnPowerCheck(Check);
}
