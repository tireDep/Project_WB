
#include "UIWidgetBase.h"

#include "API_DebugUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelSlot.h"

UUIWidgetBase::UUIWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 초기화
	UIType = EUIType::UT_Invalid;
	bIsShow = false;
	bHasFocus = false;
}

// UI 표시 제어
void UUIWidgetBase::SetShow(bool bShow)
{
	if (bIsShow == bShow)
		return;

	bIsShow = bShow;
	if (bIsShow == false )
	{
		// UI 표시
		SetVisibility(ESlateVisibility::Collapsed);
		OnShow();
	}
	else
	{
		// ui 끄기
		SetVisibility(ESlateVisibility::Visible);
		OnHide();
	}

	// 포커스 해제
	if ( bHasFocus == true )
		bHasFocus = false;
}

// todo : 추후 구현
void UUIWidgetBase::SetUIZOrder(int NewZOrder)
{
	FAPI_DebugUtils::ShowWarning("SetUIZOrder is not complete!");
}

// 포커스 획득. 블루프린트 추가 구현 가능
void UUIWidgetBase::OnGaindFocus_Implementation()
{
	bHasFocus = true;
}

// 포커스 상실. 블루프린트 추가 구현 가능
void UUIWidgetBase::OnLostFocus_Implementation()
{
	bHasFocus = false;
}

// AddToViewprot시 호출. Viewport에 Add될 때 마다 호출됨
void UUIWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	// UI 초기화
	OnInitialize();
}

// RemoveFromParent(RemoveFromViewport)시 호출. Viewport에서 remove될 때마다 호출됨
void UUIWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

// UI 열때 자식 클래스에서 오버라이드
void UUIWidgetBase::OnShow_Implementation()
{
}

// UI 끌때 자식 클래스에서 오버라이드
void UUIWidgetBase::OnHide_Implementation()
{
}

// UI 초기화 할때 자식 클래스에서 오버라이드
void UUIWidgetBase::OnInitialize_Implementation()
{
}

UUIManagerSubsystem* UUIWidgetBase::GetUISubsystem() const
{
	if ( UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		return GameInstance->GetSubsystem<UUIManagerSubsystem>();
	}
	return nullptr;
}
