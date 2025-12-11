#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "ItemNoteWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class PROJECT_WB_API UItemNoteWidget : public UUIWidgetBase
{
	GENERATED_BODY()

public:
	UItemNoteWidget(const FObjectInitializer& ObjectInitializer);

public:

protected:
	// UI 표시 될 때 호출 함수
	virtual void OnShow_Implementation() override;

	// UI 끌 때 호출 함수
	virtual void OnHide_Implementation() override;
	
	// 초기화 시 호출 함수
	virtual void OnInitialize_Implementation() override;

	// 위젯 바인딩(UMG 에디터에서 생성한 컴포넌트)
	// 닫기 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	// 아이템 정보 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* ItemInfoImage;

	// 아이템 정보 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemInfoText;

	// // 아이템 버튼
	// 없음,  _1 ~ _8 까지 존재
	// UPROPERTY(meta = (BindWidget))
	// UButton* ItemButton;

private:
	
};