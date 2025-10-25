#pragma once

#include "CoreMinimal.h"
#include "UITypes.generated.h" // sturct 생성시 헤더파일 추가 필요!

UENUM(BlueprintType)
enum class EUIType : uint8
{
	UT_Invalid = 0,
	UT_Dialog,
	UT_Max
};

UENUM(BlueprintType)
enum class EUILayer : uint8
{
	UL_Invalid = 0,
	UL_Dialog,
	UI_Max
};

USTRUCT(BlueprintType)
struct FUIConfig
{
	GENERATED_BODY()

	// UI 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EUIType UIType;

	// UI 레이어
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EUILayer UILayer;

	// 표시 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (EditCondition = false, EditConditionHides))
	bool bIsShow;

	// 모달 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bIsModal;
	
	// // ESC로 닫기 가능 여부
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	// bool bCanCloseEsc;

	// // 단일 인스턴스 여부
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (EditConditionHides))
	// bool bIsSingleton;

	FUIConfig()
	{
		Init();
	}

	void Init()
	{
		UIType = EUIType::UT_Invalid;
		UILayer = EUILayer::UL_Invalid;
		bIsShow = false;
		bIsModal = false;
		// bCanCloseEsc = false;
		// bIsSingleton = false;
	}
};
