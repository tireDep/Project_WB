#pragma once

#include "CharacterEnumType.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	CT_Invalid UMETA(DisplayName = "CT_Invalid"),
	CT_Player UMETA(DisplayName = "CT_Player"),
	CT_NPC UMETA(DisplayName = "CT_NPC"),
	CT_Max UMETA(DisplayName = "CT_Max"),
};

UENUM(BlueprintType)
enum class ECharacterID  : uint8
{
	CI_Invalid = 0,
	CI_Player = 1,
	CI_NPC_01 = 2,
	CI_NPC_02 = 3,
	CI_Max,
};
