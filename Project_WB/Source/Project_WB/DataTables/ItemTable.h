#pragma once
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "ItemTable.generated.h"

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

	// 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	FName ItemDescription;

	// character's ID, dialog ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	TMap<ECharacterID, int> DialogInfo;

	// 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Graphic")
	UPaperSprite* ItemSprite;

	// 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Graphic")
	UTexture2D* ItemIcon;

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
		ItemIcon = nullptr;
	}
};

