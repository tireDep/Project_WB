
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

public:
	virtual void Tick(float DeltaTime) override;
};
