
#include "DialogWidget.h"

UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsShow = false;
	UIType = EUIType::UT_Dialog;
}
