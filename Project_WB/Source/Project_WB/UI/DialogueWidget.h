
#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "DialogueWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;

UCLASS()
class PROJECT_WB_API UDialogueWidget : public UUIWidgetBase
{
	GENERATED_BODY()

public:
	UDialogueWidget(const FObjectInitializer& ObjectInitializer);

	// 대화문 설정
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void UpdateDialogueText(int DialogueIndex);

	// 다음 버튼 선택시_대화문 설정
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnNextButtonClicked();

protected:
	virtual void OnShow_Implementation() override;
	virtual void OnHide_Implementation() override;
	virtual void OnInitialize_Implementation() override;
	virtual void OnGaindFocus_Implementation() override;
	virtual void OnLostFocus_Implementation() override;

	// 현재 대화 정보
	UPROPERTY()
	int CurDialogueID;

	// 현재 대사 정보
	UPROPERTY()
	int CurScriptID;
	
	// 위젯 바인딩(UMG 에디터에서 생성한 컴포넌트)
	// 이름
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScriptName;

	// 대사
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScriptDesc;

	// 캐릭터 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImage;

	// 대사 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* ScriptImage;

	// 다음 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* NextButton;
	
	// 탐정수첩 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* ItemNoteButton;

	// 제시 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* SuggestButton;

	// 대화 종료 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
};
