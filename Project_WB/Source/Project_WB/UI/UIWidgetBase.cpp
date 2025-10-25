
#include "UIWidgetBase.h"

UUIWidgetBase::UUIWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIConfig.Init();
}

// UI 표시 제어
void UUIWidgetBase::SetShowUI(bool bShow)
{
	if (UIConfig.bIsShow == bShow)
		return;

	UIConfig.bIsShow = bShow;
	if (UIConfig.bIsShow == false )
	{
		SetVisibility(ESlateVisibility::Collapsed);
		
		OnUIClosedEvent();
		OnUIClosed.Broadcast(this);
		return;	
	}

	SetVisibility(ESlateVisibility::Visible);
	
	OnUIOpenedEvent();
	OnUIOpened.Broadcast(this);
}

// AddToViewprot시 호출. Viewport에 Add될 때 마다 호출됨
void UUIWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	OnUIInitialized();
}

// RemoveFromParent(RemoveFromViewport)시 호출. Viewport에서 remove될 때마다 호출됨
void UUIWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

// 위젯 키 입력 받아오기
FReply UUIWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// if ( UIConfig.bCanCloseEsc == true && InKeyEvent.GetKey() == EKeys::Escape )
	// {
	// 	SetShowUI(false);
	// 	return FReply::Handled();
	// }
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
