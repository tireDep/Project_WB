
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UITypes.h"
#include "Project_WB/Subsystems/UIManagerSubsystem.h"
#include "UIWidgetBase.generated.h"

UCLASS(Abstract, BlueprintType,Blueprintable)
class PROJECT_WB_API UUIWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UUIWidgetBase(const FObjectInitializer& ObjectInitializer);

	// UI 표시 제어
	UFUNCTION(BlueprintCallable, Category="UI")
	virtual void SetShow(bool bShow);

	// UI 타입 설정
	void SetUIType(const EUIType SetUIType) { UIType = SetUIType;	}

	// todo : 추후 구현
	// ZOrder 설정
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetUIZOrder(int NewZOrder);

	// UI 표시 상태 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	bool GetShowUI() const { return bIsShow;		}

	// UI 타입 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	EUIType GetUIType() const { return UIType;		}

	// 포커스 여부 리턴
	UFUNCTION(BlueprintPure, Category="UI")
	bool GetFocusUI() const { return bHasFocus;		}

	// 포커스 획득 이벤트
	UFUNCTION(BlueprintPure, Category="UI")
	bool OnGainedFocus() { return true;	}		// BlueprintPure specifier is not allowed for functions with no return value and no output parameters.
	virtual void OnGaindFocus_Implementation();

	// 포커스 상실 이벤트
	UFUNCTION(BlueprintPure, Category="UI")
	bool OnLostFocus() { return true;	}		// BlueprintPure specifier is not allowed for functions with no return value and no output parameters.
	virtual void OnLostFocus_Implementation();

protected:
	// NativeConstruct 오버라이드
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// UI가 표시될 때 호출
	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void OnShow();
	virtual void OnShow_Implementation();
	
	// UI가 숨겨질 때 호출 (자식 클래스에서 오버라이드)
	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void OnHide();
	virtual void OnHide_Implementation();
	
	// UI 초기화 (자식 클래스에서 오버라이드) 
	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void OnInitialize();
	virtual void OnInitialize_Implementation();

	// UI Subsystem 접근 헬퍼
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUIManagerSubsystem* GetUISubsystem() const;

	// UI 설정 정보
	// UI 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EUIType UIType;

	// 표시 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (EditCondition = false, EditConditionHides))
	bool bIsShow;

	// 포커스 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bHasFocus;
};
