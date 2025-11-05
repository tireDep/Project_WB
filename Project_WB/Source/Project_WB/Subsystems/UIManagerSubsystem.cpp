
#include "UIManagerSubsystem.h"

#include "API_DebugUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/UI/DialogueWidget.h"
#include "Project_WB/UI/UIWidgetBase.h"

// 초기화
void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 정보 초기화
	UIWidgetMap.Empty();
	UILayerInfoMap.Empty();
	CurrentFocusedUI = nullptr;
	VisibleUIList.Empty();
	
	InitializeUILayerInfo();
	InitializeWidgetClasses();

	FAPI_DebugUtils::ShowInfo( "UUIManagerSubsystem::Initialize" );
}

// 정리
void UUIManagerSubsystem::Deinitialize()
{
	// 모든 UI 정리
	for (auto& UI : UIWidgetMap)
	{
		if (UI.Value == nullptr)
			continue;
		
		UI.Value->RemoveFromParent();
	}

	UIWidgetMap.Empty();

	// 정리할때는 마지막에 호출
	Super::Deinitialize();
}

// UI 위젯 가져오기
UUIWidgetBase* UUIManagerSubsystem::GetUIWidget(EUIType UIType)
{
	if (UIType == EUIType::UT_Invalid || UIType == EUIType::UT_Max)
	{
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::GetUIWidget Invalid UIType returned" );
		return nullptr;	
	}

	// 생성된 위젯이 있는지 탐색
	UUIWidgetBase** FindWidget = UIWidgetMap.Find(UIType);
	if (FindWidget != nullptr && *FindWidget != nullptr)
	{
		return *FindWidget;
	}

	// 없으면 새로 생성
	UUIWidgetBase* NewWidget = CreateUI(UIType);
	if (NewWidget != nullptr)
	{
		UIWidgetMap.Add(UIType, NewWidget);
	}
	else
	{
		FString TypeStringForError = *UEnum::GetValueAsString(UIType);
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::GetUIWidget create widget fail " + TypeStringForError );
	}

	return NewWidget;
}

void UUIManagerSubsystem::SetShowUI(EUIType UIType, bool bShow, bool bForceFocus)
{
	// UI 가져오기. 없으면 자동 생성
	UUIWidgetBase* ReturnWidget = GetUIWidget(UIType);
	if (ReturnWidget == nullptr)
	{
		FString TypeStringForError = *UEnum::GetValueAsString(UIType);
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::SetShowUI find fail " + TypeStringForError );
		return;
	}

	// UI 표시 제어
	ReturnWidget->SetShow(bShow);

	if (bShow == true)
	{
		// 표시 중인 UI 목록에 추가
		VisibleUIList.AddUnique(UIType);

		// 포커스 설정
		if (bForceFocus || CurrentFocusedUI == nullptr)
			SetFocusedUI(UIType);
	}
	else
	{
		// 표시 중인 UI 목록에서 제거
		VisibleUIList.Remove(UIType);

		// 포커스 해제된 UI였다면 다른 UI로 포커스 이동
		if (CurrentFocusedUI == ReturnWidget)
		{
			CurrentFocusedUI = nullptr;

			if (VisibleUIList.Num() > 0)
			{
				EUIType HighestZOrderType = VisibleUIList[0];
				int HighestZOrder = -1;

				for (EUIType VisibleType : VisibleUIList)
				{
					FUILayerInfo* LayerInfo = UILayerInfoMap.Find(VisibleType);
					if (LayerInfo == nullptr)
						continue;

					HighestZOrder = LayerInfo->ZOrder;
					HighestZOrderType = VisibleType;
				}

				SetFocusedUI(HighestZOrderType);
			}
		}
	}

	// 입력 모드 업데이트(UI 상태에 따라 자동 조정)
	UpdateInputMode();
}

bool UUIManagerSubsystem::IsUIVisible(EUIType UIType) const
{
	// UI 표시 상태 반환
	const UUIWidgetBase* const* FindWidget = UIWidgetMap.Find(UIType);
	if (FindWidget != nullptr && *FindWidget != nullptr)
	{
		return (*FindWidget)->GetVisibility() == ESlateVisibility::Visible ||
			(*FindWidget)->GetVisibility() == ESlateVisibility::SelfHitTestInvisible;
	}
	
	return false;
}

void UUIManagerSubsystem::HideAllUI(const TArray<EUIType> ExceptTypes)
{
	// 숨김 UI 목록 생성
	TArray<EUIType> HideUIList;
	for (const auto& Pair : UIWidgetMap)
	{
		if (ExceptTypes.Contains(Pair.Key) == true && Pair.Value != nullptr)
			continue;

		HideUIList.Add(Pair.Key);
	}

	// UI 숨기기
	for (EUIType UIType : HideUIList)
	{
		SetShowUI(UIType, false);
	}
}

void UUIManagerSubsystem::SetFocusedUI(EUIType UIType)
{
	UUIWidgetBase* Widget = GetUIWidget(UIType);
	if (Widget == nullptr)
	{
		return;	
	}

	// 이전 포커스 UI의 포커스 해제
	if (CurrentFocusedUI && CurrentFocusedUI != Widget)
	{
		CurrentFocusedUI->OnLostFocus();
	}

	// 새 UI에 포커스
	CurrentFocusedUI = Widget;
	CurrentFocusedUI->OnGainedFocus();
}

void UUIManagerSubsystem::SetUIZOrder(EUIType UIType, int NewZOrder)
{
	UUIWidgetBase* Widget = GetUIWidget(UIType);
	if (Widget == nullptr)
	{
		return;	
	}

	Widget->SetUIZOrder(NewZOrder);

	// 레이어 정보 업데이트
	if (FUILayerInfo* LayerInfo = UILayerInfoMap.Find(UIType))
	{
		LayerInfo->ZOrder = NewZOrder;
	}
}

void UUIManagerSubsystem::BringUIToFront(EUIType UIType)
{
	// 현대 최대 ZOrder 찾기
	int MaxZOrder = 0;
	for (const auto& Pair : UILayerInfoMap)
	{
		if (Pair.Value.ZOrder <= MaxZOrder)
			continue;

		MaxZOrder = Pair.Value.ZOrder;
	}

	// 최대값 + 1로 설정
	SetUIZOrder(UIType, MaxZOrder + 1);
}

UUIWidgetBase* UUIManagerSubsystem::CreateUI(EUIType UIType)
{
	FString TypeStringForError = *UEnum::GetValueAsString(UIType);
	
	// UI 위젯 클래스가 설정되어 있는지 확인
	TSubclassOf<UUIWidgetBase>* WidgetClass = UIWidgetClasses.Find(UIType);
	if (!WidgetClass || !(*WidgetClass))
	{
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::CreateUI class not exist " + TypeStringForError );
		return nullptr;
	}

	// 월드 컨텍스트 가져오기
	UWorld* World = GetWorld();
	if (World ==nullptr)
	{
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::CreateUI world is nullptr " );
		return nullptr;
	}

	// 위젯 생성
	UUIWidgetBase* NewWidget = CreateWidget<UUIWidgetBase>(World, *WidgetClass);
	if (NewWidget == nullptr)
	{
		FAPI_DebugUtils::ShowError( "UUIManagerSubsystem::CreateUI fail " + TypeStringForError );
		return nullptr;
	}

	// UI 타입 설정
	NewWidget->SetUIType(UIType);

	// 뷰포트 추가, 기본적으로 숨김상태
	NewWidget->AddToViewport();
	NewWidget->SetVisibility(ESlateVisibility::Collapsed);

	// ZOrder 설정
	if (FUILayerInfo* LayerInfo = UILayerInfoMap.Find(UIType))
	{
		NewWidget->SetUIZOrder(LayerInfo->ZOrder);
	}

	return NewWidget;
}

void UUIManagerSubsystem::InitializeUILayerInfo()
{
	// 기본 ZOrder 설정
	// 숫자가 높을수록 상위 레이어
	// UILayerInfoMap.Add(EUIType::UT_Dialogue, FUILayerInfo{ EUIType::UT_Invalid, 0, false }); // 참고용
	// UILayerInfoMap.Add(EUIType::UT_Max, FUILayerInfo{ EUIType::UT_Max, 30, true }); // 참고용
	
	UILayerInfoMap.Add(EUIType::UT_Dialogue, FUILayerInfo{ EUIType::UT_Dialogue, 15, false });
}

void UUIManagerSubsystem::InitializeWidgetClasses()
{
	UIWidgetClasses.Add(EUIType::UT_Dialogue, UDialogueWidget::StaticClass());
}

void UUIManagerSubsystem::UpdateInputMode()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController == nullptr)
		return;

	// 입력을 차단하는 UI가 있는지 확인
	bool bHasBlockingUI = false;
	for (EUIType VisibleType : VisibleUIList)
	{
		FUILayerInfo* LayerInfo = UILayerInfoMap.Find(VisibleType);
		if (LayerInfo == nullptr)
			continue;

		if (LayerInfo->bBlocksInput == false)
			continue;

		bHasBlockingUI = true;
		break;
	}

	// 입력 모드 설정
	if (bHasBlockingUI == true)
	{
		// UI만 입력 받기
		FInputModeUIOnly InputMode;
		if (CurrentFocusedUI != nullptr)
		{
			InputMode.SetWidgetToFocus(CurrentFocusedUI->TakeWidget());
		}

		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
	else if (VisibleUIList.Num() > 0)
	{
		// 게임과 UI 모두 입력 받기
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
	else
	{
		// 게임만 입력 받기
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}
