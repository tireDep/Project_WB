#pragma once
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "ItemTable.generated.h"

// 조건 타입 열거형
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	IC_BASIC,		// 기본 정보
	IC_MAP,			// 맵에서 수집
	IC_DIALOGUE,	// 대화 중 수집
};

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
{
	GENERATED_BODY()

	// 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	int ItemID;

	// 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	FName ItemName;
	
	// 카테고리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	EItemCategory ItemCategory;

	// 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	FName ItemDescription;
	
	// 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Graphic")
	UPaperSprite* ItemSprite;

	FItemTableData()
	{
		Init();
	}

	void Init()
	{
		ItemID = 0;
		ItemName = FName("DefaultName");
		ItemDescription = FName("DefaultDesc");
		ItemSprite = nullptr;
	}
};

