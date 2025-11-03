
#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "DialogueWidget.generated.h"

UCLASS()
class PROJECT_WB_API UDialogueWidget : public UUIWidgetBase
{
	GENERATED_BODY()

public:
	UDialogueWidget(const FObjectInitializer& ObjectInitializer);

	// 대화문 설정
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void SetDialogueText(int DialogueIndex);

protected:
	virtual void OnShow_Implementation() override;
	virtual void OnHide_Implementation() override;
	virtual void OnInitialize_Implementation() override;
	virtual void OnGaindFocus_Implementation() override;
	virtual void OnLostFocus_Implementation() override;

	// // 위젯 바인딩(UMG 에디터에서 생성한 컴포넌트)
	// UPROPERTY(meta = (BindWidget))
	// UTextBlock* DialogueTextBlock;
	// 
	// UPROPERTY(meta = (BindWidget))
	// UImage* BackgroundImage;
};
