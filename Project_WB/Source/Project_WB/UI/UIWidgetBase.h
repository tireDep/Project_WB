
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UITypes.h"
#include "UIWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FonUIStateChange, class UUIWidgetBase*, Widget);

UCLASS(Abstract, BlueprintType,Blueprintable)
class PROJECT_WB_API UUIWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UUIWidgetBase(const FObjectInitializer& ObjectInitializer);

	// UI 표시 제어
	UFUNCTION(BlueprintCallable, Category="UI")
	virtual void SetShowUI(bool bShow);

	// UI 표시 상태 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	bool GetShowUI() const { return UIConfig.bIsShow;	}

	// UI 타입 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	EUIType GetUIType() const { return UIConfig.UIType;	}

	// UI 레이어 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	EUILayer GetUILayer() const { return UIConfig.UILayer;	}
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	// >> 블루프린트 구현 이벤트들
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnUIOpenedEvent();

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnUIClosedEvent();

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnUIInitialized();
	// <<

	// UI 설정 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	FUIConfig UIConfig;

	// UI 상태 변경 이벤트
	UPROPERTY(BlueprintAssignable)
	FonUIStateChange OnUIOpened;

	UPROPERTY(BlueprintAssignable)
	FonUIStateChange OnUIClosed;
};
