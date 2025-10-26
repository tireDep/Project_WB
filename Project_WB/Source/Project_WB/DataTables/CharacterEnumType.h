#pragma once

#include "CharacterEnumType.generated.h"

// 캐릭터 타입
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	CT_INVALID,
	CT_PLAYER,
	CT_NPC,
	CT_MAX,
};

// 캐릭터 이넘 ID
UENUM(BlueprintType)
enum class ECharacterID  : uint8
{
	CI_INVALID	= 0,
	CI_PLAYER	= 1,
	CI_NPC_01	= 2,
	CI_NPC_02	= 3,
	CI_NPC_03	= 4,
	CI_NPC_04	= 5,
	CI_NPC_05	= 6,
	CI_NPC_06	= 7,
	CI_Max,
};
