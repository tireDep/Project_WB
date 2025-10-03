#pragma once

#include "CharacterEnumType.generated.h"

// 캐릭터 타입
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	CT_Invalid UMETA(DisplayName = "CT_Invalid"),
	CT_Player UMETA(DisplayName = "CT_Player"),
	CT_NPC UMETA(DisplayName = "CT_NPC"),
	CT_Max UMETA(DisplayName = "CT_Max"),
};

// 캐릭터 이넘 ID
UENUM(BlueprintType)
enum class ECharacterID  : uint8
{
	CI_Invalid = 0,
	CI_Player = 1,
	CI_NPC_01 = 2,
	CI_NPC_02 = 3,
	CI_Max,
};
