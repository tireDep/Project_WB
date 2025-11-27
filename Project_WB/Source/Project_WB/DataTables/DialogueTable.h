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

	// 대사 ID
	// * 중복되는 값 불가능!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int ScriptID;
	
	// 캐릭터 ID
	// * CI_PLAYER : 플레이어
	// * CI_NPC_01 ~ CI_NPC_06 : NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	ECharacterID CharacterID;
	
	// 출력 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptShowName;
	
	// 출력 대사
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptShowDesc;
	
	// 캐릭터 이미지 파일
	// * 파일명을 대문자로 확장자 없이 작성
	// * 정해진 경로에 파일이 존재해야함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString CharacterImageName;

	// 캐릭터 이미지 스프라이트 캐시 데이터
	UPROPERTY()
	UPaperSprite* CachedCharacterSprite;
	
	// 이미지 위치
	// * true : 오른쪽, false : 왼쪽
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	bool CharacterImagePosition;
	
	// 대사 이미지 파일
	// * 파일명을 대문자로 확장자 없이 작성
	// * 정해진 경로에 파일이 존재해야함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	FString ScriptImageName;

	// 대사 이미지 스프라이트 캐시 데이터
	UPROPERTY()
	UPaperSprite* CachedImageSprite;
	
	// 획득 가능 아이템 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int GainItemID;

	// TODO : 
	// 표시 툴팁 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script Table")
	int ShowTooltipID;

	// TODO
	// 추가효과가 붙는다면 이쪽에 추가

	FScriptTableData()
	{
		Init();
	}
	
	void Init()
	{
		ScriptID				= VALUE_NUMBER_ZERO;
		CharacterID				= ECharacterID::CI_INVALID;
		ScriptShowName			= FString("");
		ScriptShowDesc			= FString("");
		CharacterImageName		= FString("");
		CachedCharacterSprite	= nullptr;
		CharacterImagePosition	= false;
		ScriptImageName			= FString("");
		CachedImageSprite		= nullptr;
		GainItemID				= VALUE_NUMBER_ZERO;
		ShowTooltipID			= VALUE_NUMBER_ZERO;
	}
};

// 대화 테이블 구조체
USTRUCT(BlueprintType)
struct FDialogueTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 대화 ID
	// * 중복되는 값 불가능!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int DialogueID;
	
	// 표시할 대사 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int ShowScriptID;
	
	// 기본 다음 진행 대화 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table")
	int DefaultNextDialogueID;
	
	// 대화 분기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table Condition")
	EConditionType ConditionType;

	// 대화 분기 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue Table Condition")
	FString ConditionValue;

	// 대화 분기 다음 진행 대화 ID
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
