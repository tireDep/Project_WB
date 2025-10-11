#pragma once
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "DialogTable.generated.h"

USTRUCT(BlueprintType)
struct FDialogTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	int DialogID;

	// 대화 표시 스프라이트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	UPaperSprite* DialogSprite;

	// 대화 표시 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	FString DialogShowName;

	// 대화 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	FString DialogString;

	// 다음 다이얼로그 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	int NextDialogID;

	// 획득 아이템 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	int GainItemID;

	// 이미지 스프라이트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog Table")
	UPaperSprite* DialogImageSprite;

	FDialogTableData()
	{
		Init();
	}
	
	void Init()
	{
		DialogID = 0;
		DialogSprite = nullptr;
		DialogShowName = FString("Default");
		DialogString = FString("Default");
		NextDialogID = 0;
	}

	int GetDialogID() const { return DialogID; }
	const UPaperSprite* GetDialogSprite() const { return DialogSprite; }
	FString GetDialogShowName() const { return DialogShowName; }
	FString GetDialogString() const { return DialogString; }
	int GetNextDialogID() const { return NextDialogID; }
};
