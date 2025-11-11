
#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "BasicItem.generated.h"

UCLASS(Blueprintable)
class PROJECT_WB_API ABasicItem : public AItemBase
{
	GENERATED_BODY()

public:
	ABasicItem();

	// 캐릭터별 대화 정보 가져오기
	UFUNCTION(BlueprintCallable)
	int GetDialogueIndex(ECharacterID CharacterID);

	// 대사 정보 설정
	UFUNCTION(BlueprintCallable)
	void SetDialogueTextInfo(ECharacterID CharacterID, UUserWidget* Widget);

protected:
	virtual void BeginPlay() override;

	// 마우스 입력 처리
	UFUNCTION(BlueprintCallable)
	virtual void OnItemMouseOver(AActor* Actor) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnItemMouseExit(AActor* Actor) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnItemMouseClick(AActor* Actor) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnItemMouseReleased(AActor* Actor) override;
	

public:
	virtual void Tick(float DeltaTime) override;
};
