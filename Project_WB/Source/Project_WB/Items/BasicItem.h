
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

protected:
	virtual void BeginPlay() override;

	// 마우스 입력 처리
	UFUNCTION()
	virtual void OnItemMouseOver(AActor* Actor) override;

	UFUNCTION()
	virtual void OnItemMouseExit(AActor* Actor) override;

	UFUNCTION()
	virtual void OnItemMouseClick(AActor* Actor) override;

	UFUNCTION()
	virtual void OnItemMouseReleased(AActor* Actor) override;
	

public:
	virtual void Tick(float DeltaTime) override;
};
