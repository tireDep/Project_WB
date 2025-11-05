#pragma once

#include "CoreMinimal.h"
#include "UITypes.generated.h" // sturct 생성시 헤더파일 추가 필요!

UENUM(BlueprintType)
enum class EUIType : uint8
{
	UT_Invalid = 0,
	UT_Dialogue,
	UT_Max
};

UENUM(BlueprintType)
enum class EUILayer : uint8
{
	UL_Invalid = 0,
	UL_Dialog,
	UI_Max
};
