
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "PlayerActor.generated.h"

class UInteractionComponent;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	PS_INVALID			UMETA(DisplayName = "INVALID"),
	PS_IDLE				UMETA(DisplayName = "IDLE"),
	PS_TALKING_ITEM		UMETA(DisplayName = "TALIKING_ITEM"),
	PS_TALKING_NPC		UMETA(DisplayName = "TALIKING_NPC"),
};

USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_BODY()

	// 아이템 아이디
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemID;										

	// 상호작용한 캐릭터 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<ECharacterID> InteractionCharacterIDs;	

	FItemInformation()
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
	EPlayerState GetState()	{ return CurrentState; }

	// 플레이어 상태 설정
	void SetState(EPlayerState NewState) { CurrentState = NewState; }

	// 아이템 획득
	void AddGainedItem(int ItemID);

	// 아이템 정보 체크
	bool CheckGainedItemInfo(int ItemID, ECharacterID CheckCharacterID = ECharacterID::CI_INVALID);

	// 아이템 정보 업데이트
	void UpdateGainedItemInfo(int ItemID, ECharacterID UpdateCharacterID);

	// 획득한 아이템 정보 반환
	const TArray<FItemInformation> GetGainedItems() { return ItemInformations;}

	// 상호작용 컴포넌트 반환
	UInteractionComponent* GetInteractionComponent() const { return InteractionComp;}
	
protected:
	// 플레이어 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	EPlayerState CurrentState;

	// 보유한 아이템 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	TArray<FItemInformation> ItemInformations;

	// 대화 UI 상호작용 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	TObjectPtr<UInteractionComponent> InteractionComp; 
};
