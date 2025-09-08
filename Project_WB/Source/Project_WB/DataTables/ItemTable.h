#pragma once
#include "Engine/DataTable.h"
#include "PaperSpriteComponent.h"
#include "ItemTable.generated.h"

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	FName ItemDescription;

	// character's ID, interaction ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Table")
	TMap<int32, int32> InteractionInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Graphic")
	UPaperSprite* ItemSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Graphic")
	UTexture2D* ItemIcon;

	FItemTableData()
	{
		ItemID = 0;
		ItemName = FName("DefaultName");
		ItemDescription = FName("DefaultDesc");
		ItemSprite = nullptr;
		ItemIcon = nullptr;
	}
};

