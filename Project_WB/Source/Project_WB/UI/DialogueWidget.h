
#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "DialogueWidget.generated.h"

enum class EPlayerState : uint8;
class UTextBlock;
class UImage;
class UButton;
class APlayerActor;

USTRUCT(BlueprintType)
struct FDialogueResult
{
	GENERATED_BODY()

	// 획득한 아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GainItemID;

	// 변경할 플레이어 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerState ChangeState;

	FDialogueResult()
	{
		Init();
	}

	void Init()
	{
		GainItemID		= 0;
		ChangeState		= EPlayerState::PS_INVALID;
	}
};

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

	// 제시 버튼 선택시_대화 상태에 따른 ui 변경
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnSuggestButtonClicked();

	// 대화 종료 버튼 선택시_대화 상태 종료 처리
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnExitButtonClicked();

	// 탐정 수첩 보기 버튼 선택시_탐정 수첩 UI 열기
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnItemNoteButtonClicked();

protected:
	// UI 표시 될 때 호출 함수
	virtual void OnShow_Implementation() override;

	// UI 끌 때 호출 함수
	virtual void OnHide_Implementation() override;

	// 초기화 시 호출 함수
	virtual void OnInitialize_Implementation() override;

	// 포커스 얻을 때 호출 함수
	virtual void OnGaindFocus_Implementation() override;

	// 포커스 잃을 때 호출 함수
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

	// 오른쪽 캐릭터 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImageRight;

	// 왼쪽 캐릭터 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImageLeft;

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

private:
	// 마지막 대사인지 체크
	bool CheckIsFinalScript(const FDialogueTableData* PtDialogueTableData);
};
