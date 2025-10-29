#pragma once
#include "CharacterEnumType.h"
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "DialogTable.generated.h"

// 조건 타입 열거형
UENUM(BlueprintType)
enum class EConditionType : uint8
{
	CT_HAS_ITEM,	// 아이템 보유
	CT_PROGRESS,	// 진행도
	CT_NONE,		// 조건 없음
};

// 다음 대사 세팅용 조건 구조체
USTRUCT(BlueprintType)
struct FDialogCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FDialogCondition")
	EConditionType	ConditionType;		// 대사 조건 타입
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FDialogCondition")
	FString			ConditionValue;		// 대사 조건 값
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FDialogCondition")
	int             ScriptID;			// 스크립트 ID

	FDialogCondition()
	{
		Init();
	}

	void Init()
	{
		ConditionType = EConditionType::CT_NONE;
		ConditionValue = "";
		ScriptID = 0;
	}
};

// 대사 설정 테이블 구조체
USTRUCT(BlueprintType)
struct FScriptTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int ScriptID;

	// 대화 표시 스프라이트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	UPaperSprite* ScriptSprite;

	// 대화 표시 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptShowName;

	// 대화 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptString;

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

	// // 조건 분기 다이얼로그
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	// TArray<FDialogCondition> DialogConditions;

	FScriptTableData()
	{
		Init();
	}
	
	void Init()
	{
		ScriptID = 0;
		ScriptSprite = nullptr;
		ScriptShowName = FString("Default");
		ScriptString = FString("Default");
		ScriptImageSprite = nullptr;
		GainItemID = 0;
		TooltipID = 0;
		// DialogConditions.Empty();
	}
};

// 대화문 설정 구조체
USTRUCT(BlueprintType)
struct FDialogueTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 대사 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int StartScriptID;

	// 1안
	// 조건 분기 다이얼로그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	TArray<FDialogCondition> NextDialogueConditions;

	// 2안
	// 조건 분기 다이얼로그 개별 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int FirstNextScriptID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	EConditionType FirstConditionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	FString FirstScirptCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int SecondNextScriptID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	EConditionType SecondConditionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	FString SecondScirptCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int ThirdNextScriptID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	EConditionType ThirdConditionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	FString ThirdScirptCondition;

	FDialogueTableData()
	{
		Init();
	}
	
	void Init()
	{
		StartScriptID = 0;
		NextDialogueConditions.Empty();
		
		FirstNextScriptID = 0;
		FirstConditionType = EConditionType::CT_NONE;
		FirstScirptCondition = FString("");
		SecondNextScriptID = 0;
		SecondConditionType = EConditionType::CT_NONE;
		SecondScirptCondition = FString("");
		ThirdNextScriptID = 0;
		ThirdConditionType = EConditionType::CT_NONE;
		ThirdScirptCondition = FString("");
	}
};
