
#pragma once

#include "CoreMinimal.h"
#include "CharacterActorBase.h"
#include "NPCActorBase.generated.h"

UCLASS()
class PROJECT_WB_API ANPCActorBase : public ACharacterActorBase
{
	GENERATED_BODY()

public:
	ANPCActorBase();

protected:
	virtual void BeginPlay() override;

	// ItemCheckInfo

public:
	virtual void Tick(float DeltaTime) override;
};
