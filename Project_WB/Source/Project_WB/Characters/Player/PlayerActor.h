
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "PlayerActor.generated.h"

enum PlayerState
{
	PS_IDLE,
	PS_TALKING_ITEM,
	PS_TALKING_NPC,
};

struct ItemInformation
{
	int ItemID;										// 아이템 아이디
	TSet<ECharacterID> InteractionCharacterIDs;		// 상호작용한 캐릭터 정보

	ItemInformation()
	{
		Init();
	}

	void Init()
	{
		ItemID = 0;
		InteractionCharacterIDs.Empty();
	}
};

UCLASS()
class PROJECT_WB_API APlayerActor : public ACharacterActorBase
{
	GENERATED_BODY()

public:
	APlayerActor();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	// 플레이어 상태 반환
	PlayerState GetState()	{ return CurrentState; }

	// 플레이어 상태 설정
	void SetState(PlayerState NewState) { CurrentState = NewState; }

	// 아이템 획득
	void AddGainedItem(int ItemID);

	// 아이템 정보 체크
	bool CheckGainedItemInfo(int ItemID, ECharacterID CheckCharacterID = ECharacterID::CI_INVALID);

	// 아이템 정보 업데이트
	void UpdateGainedItemInfo(int ItemID, ECharacterID UpdateCharacterID);

	// 획득한 아이템 정보 반환
	const TArray<ItemInformation> GetGainedItems() { return ItemInformations;}
	
private:
	// 플레이어 상태
	PlayerState CurrentState;

	// 보유한 아이템 정보
	TArray<ItemInformation> ItemInformations;
};
