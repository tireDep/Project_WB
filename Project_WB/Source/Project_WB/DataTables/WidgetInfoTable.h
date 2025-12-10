#pragma once
#include "Engine/DataTable.h"
#include "Project_WB/UI/UITypes.h"
#include "WidgetInfoTable.generated.h"

USTRUCT(BlueprintType)
struct FWidgetInfoTable : public FTableRowBase
{
	GENERATED_BODY()

	// 위젯 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetInfo Table")
	EUIType UIType;

	// 위젯 블루프린트 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetInfo Table")
	FString PathWBP;

	// 위젯 ZOrder
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetInfo Table")
	int WidgetZOrder;

	FWidgetInfoTable()
	{
		Init();
	}

	void Init()
	{
		UIType = EUIType::UT_Invalid;
		PathWBP = "";
		WidgetZOrder = 0;
	}
};
