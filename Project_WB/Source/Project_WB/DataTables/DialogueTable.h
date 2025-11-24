#pragma once
#include "CharacterEnumType.h"
#include "IPropertyTable.h"
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "DialogueTable.generated.h"

// TODO : 공용 사용으로 옮기기?
constexpr int VALUE_NUMBER_ZERO = 0;

// 조건 타입 열거형
UENUM(BlueprintType)
enum class EConditionType : uint8
{
	CT_INVALID,
	CT_HAS_ITEM,	// 아이템 보유
	CT_PROGRESS,	// 진행도
	CT_MAX,
};

// 대사 테이블 구조체
USTRUCT(BlueprintType)
struct FScriptTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int ScriptID;

	// 대화 표시 스프라이트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	UPaperSprite* CharacterSprite;

	// 대화 표시 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptShowName;

	// 대화 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptDesc;

	// 이미지 스프라이트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	UPaperSprite* ScriptImageSprite;

	// 획득 아이템 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int GainItemID;

	// TODO : 
	// 툴팁 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int TooltipID;

	// TODO
	// 추가효과가 붙는다면 이쪽에 추가

	FScriptTableData()
	{
		Init();
	}
	
	void Init()
	{
		ScriptID = VALUE_NUMBER_ZERO;
		CharacterSprite = nullptr;
		ScriptShowName = FString("Default");
		ScriptDesc = FString("Default");
		ScriptImageSprite = nullptr;
		GainItemID = VALUE_NUMBER_ZERO;
		TooltipID = VALUE_NUMBER_ZERO;
	}
};

// 대화 테이블 구조체
USTRUCT(BlueprintType)
struct FDialogueTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 대화 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int DialogueID;
	
	// 표시할 대사 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int ShowScriptID;
	
	// 기본 다음 진행 대화 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int DefaultNextDialogueID;
	
	// 대사 분기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table Condition")
	EConditionType ConditionType;

	// 대사 분기 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table Condition")
	FString ConditionValue;

	// 대사 분기 다음 진행 대화 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table Condition")
	int ConditionNextDialogueID;

	FDialogueTableData()
	{
		Init();
	}
	
	void Init()
	{
		DialogueID						= VALUE_NUMBER_ZERO;
		ShowScriptID					= VALUE_NUMBER_ZERO;
		DefaultNextDialogueID			= VALUE_NUMBER_ZERO;
		ConditionType					= EConditionType::CT_INVALID;
		ConditionValue					= FString("");
		ConditionNextDialogueID			= VALUE_NUMBER_ZERO;
	}
};
