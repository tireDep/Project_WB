
#include "PlayerActor.h"

APlayerActor::APlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = PlayerState::PS_IDLE;
	GainedItemInfo.Empty();
}

void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 아이템 획득 처리
void APlayerActor::AddGainedItem(int ItemID)
{
	// 보유한 아이템일 경우 처리하지 않음
	if (CheckGainedItemInfo(ItemID) == true)
		return;

	TSet<ECharacterID> CharacterInfo;
	GainedItemInfo.Add(ItemID, CharacterInfo);
}

// 아이템 정보 체크
bool APlayerActor::CheckGainedItemInfo(int ItemID, ECharacterID CheckCharacterID/*= ECharacterID::CI_INVALID*/)
{
	// 보유한 아이템인지 체크
	auto FindIter = GainedItemInfo.Find(ItemID);
	if (FindIter == nullptr)
		return false;

	// 보유한 아이템이고, 캐릭터 정보가 포함되어 있는지 체크
	if (CheckCharacterID != ECharacterID::CI_INVALID)
	{
		if (FindIter->Find(CharacterID) == nullptr)
			return false;
	}

	return true;
}

// 아이템 정보 업데이트
void APlayerActor::UpdateGainedItemInfo(int ItemID, ECharacterID UpdateCharacterID)
{
	// 이미 업데이트 된 정보라면 끝냄
	if (CheckGainedItemInfo(ItemID, UpdateCharacterID) == true)
		return;

	// 아이템 상호작용 정보 업데이트
	auto FindItem = GainedItemInfo.Find(ItemID);
	if (FindItem == nullptr)
		return;

	FindItem->Add(UpdateCharacterID);
}

