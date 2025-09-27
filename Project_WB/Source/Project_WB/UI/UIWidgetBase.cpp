
#include "UIWidgetBase.h"

UUIWidgetBase::UUIWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsShow = false;
}

// UI 표시 제어
void UUIWidgetBase::SetShowUI(bool bShow)
{
	if ( bIsShow == bShow)
		return;

	bIsShow = bShow;
	if (bIsShow == false )
	{
		SetVisibility(ESlateVisibility::Collapsed);

		// 자동 종료 타이머 설정
		if (AutoCloseTimer.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(AutoCloseTimer);

		OnUIClosedEvent();
		OnUIClosed.Broadcast(this);
		
		return;	
	}

	SetVisibility(ESlateVisibility::Visible);
	
	// 자동 종료 타이머 설정
	if (UIConfig.AutoCloseTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			AutoCloseTimer,
			this,
			&UUIWidgetBase::HandleAutoClose,
			UIConfig.AutoCloseTime,
			false
			);
	}
	
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
	if (AutoCloseTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoCloseTimer);
	}
	
	Super::NativeDestruct();
}

// 위젯 키 입력 받아오기
FReply UUIWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if ( UIConfig.bCanCloseEsc == true && InKeyEvent.GetKey() == EKeys::Escape )
	{
		SetShowUI(false);
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

// 자동 종료 타이머 호출 함수
void UUIWidgetBase::HandleAutoClose()
{
	SetShowUI(false); 
}
