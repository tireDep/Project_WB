#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "ItemNoteWidget.generated.h"

class UImage;

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
	// 테스트용 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* TestImage;
private:
	
};