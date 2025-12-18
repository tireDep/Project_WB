
#include "PlayerActor.h"

#include "InteractionComponent.h"

APlayerActor::APlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = EPlayerState::PS_IDLE;
	ItemInformations.Empty();
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
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

	FItemInformation ItemInfo;
	ItemInfo.ItemID = ItemID;
	ItemInformations.Add(ItemInfo);
}

// 아이템 정보 체크
bool APlayerActor::CheckGainedItemInfo(int ItemID, ECharacterID CheckCharacterID/*= ECharacterID::CI_INVALID*/)
{
	// 보유한 아이템인지 체크
	for (FItemInformation ItemInfo : ItemInformations)
	{
		if (ItemInfo.ItemID != ItemID)
			continue;

		// 보유한 아이템일 경우, 캐릭터 정보가 포함되어 있는지 체크
		// 캐릭터 정보가 없는 경우 : 아이템 획득 시
		if (CheckCharacterID == ECharacterID::CI_INVALID)
			return true;

		// 캐릭터 정보가 있는 경우 : 탐정 수첩 상호작용 시(플레이어, npc)
		if (ItemInfo.InteractionCharacterIDs.Contains(CheckCharacterID) == true)
			return true;
	}

	return false; 
}

// 아이템 정보 업데이트
void APlayerActor::UpdateGainedItemInfo(int ItemID, ECharacterID UpdateCharacterID)
{
	for (FItemInformation ItemInfo : ItemInformations)
	{
		if (ItemInfo.ItemID != ItemID)
			continue;

		// 이미 상호작용 정보가 있다면, 추가로 저장하지 않음
		if (ItemInfo.InteractionCharacterIDs.Find(UpdateCharacterID) != nullptr)
			return;
		
		// 아이템 상호작용 정보 업데이트
		ItemInfo.InteractionCharacterIDs.Add(UpdateCharacterID);
	}
}

