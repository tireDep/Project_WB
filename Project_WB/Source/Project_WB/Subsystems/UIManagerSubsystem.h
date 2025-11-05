
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/UI/UITypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UUIWidgetBase;

// 레이어 정보 구조체
USTRUCT(BlueprintType)
struct FUILayerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIType UIType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ZOrder;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	bool bBlocksInput;

	FUILayerInfo()
		:UIType(EUIType::UT_Invalid)
		, ZOrder(0)
		, bBlocksInput(false)
	{
	}

	FUILayerInfo(EUIType UIType, int ZOrder, bool bBlocksInput)
	{
		this->UIType = UIType;
		this->ZOrder = ZOrder;
		this->bBlocksInput = bBlocksInput;
	}
};

// 모든 UI 생성, 관리, 표시 및 숨김 관리 서브시스템
UCLASS()
class PROJECT_WB_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Subsystem 초기화
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// UI 위젯 가져오기, 없으면 생성
	// UIType : 가져올 UI 타입
	UFUNCTION(BlueprintCallable, Category="UI")
	UUIWidgetBase* GetUIWidget(EUIType UIType);

	// 타입 안전한 UI 위젯 가져오기(C++ 전용)
	// T : 위젯 타입
	// UIType : 가져올 UI 타입
	// return : 타입 캐스팅된 UI 위젯 포인터, 실패시 nullptr
	// e.g. UDialogueWidget* DialogueWidget = UIManagerSubsystem->GetUIWidget<UDialogueWidget>(EUIType::Dialogue);
	template<typename T>
	T* GetUI(EUIType UIType)
	{
		static_assert(TIsDerivedFrom<T,UUIWidgetBase>::Value, "T must be derived from UIWidgetBase");
		return Cast<T>(GetUIWidget(UIType));
	}

	// UI 표시 서브시스템 제어
	// UIType : 가져올 UI 타입
	// bShow : true면 표시, false면 숨김
	// bForceFocus : true면 강제로 포커스 획득
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetShowUI(EUIType UIType, bool bShow, bool bForceFocus = false);

	// UI가 현재 표시중인지 확인
	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsUIVisible(EUIType UIType) const;

	// 모든 UI 숨기기
	// ExceptTypes : 숨기지 않을 UI 타입들
	UFUNCTION(BlueprintCallable, Category="UI")
	void HideAllUI(const TArray<EUIType> ExceptTypes);

	// UI 포커스 설정
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetFocusedUI(EUIType UIType);
	
	// 현재 포커스된 UI 가져오기
	UFUNCTION(BlueprintCallable, Category="UI")
	UUIWidgetBase* GetFocusedUI() const { return CurrentFocusedUI;	}

	// UI ZOrder 설정
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetUIZOrder(EUIType UIType, int NewZOrder);

	// UI 최상단으로 올리기
	UFUNCTION(BlueprintCallable, Category="UI")
	void BringUIToFront(EUIType UIType);

protected:
	// UI 생성
	UUIWidgetBase* CreateUI(EUIType UIType);

	// UI 레이어 정보 초기화
	void InitializeUILayerInfo();

	// UI 위젯 클래스 등록
	void InitializeWidgetClasses();

	// 입력 모드 업데이트
	void UpdateInputMode();

private:
	// UI 위젯 맵
	UPROPERTY()
	TMap<EUIType, UUIWidgetBase*> UIWidgetMap;

	// UI 타입별 위젯 클래스(에디터 설정)
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TMap<EUIType, TSubclassOf<UUIWidgetBase>> UIWidgetClasses;

	// UI 레이어 정보(ZOrder 관리)
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TMap<EUIType, FUILayerInfo> UILayerInfoMap;

	// 현재 포커스된 UI
	UPROPERTY()
	UUIWidgetBase* CurrentFocusedUI;

	// 현재 표시 중인 UI 목록(입력 모드 결정용)
	UPROPERTY()
	TArray<EUIType> VisibleUIList;
};
