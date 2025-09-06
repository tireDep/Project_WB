
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

	UFUNCTION()
	virtual void OnCharacterMouseOver(AActor* Actor) override;

	UFUNCTION()
	virtual void OnCharacterMouseExit(AActor* Actor) override;

	UFUNCTION()
	virtual void OnCharacterMousePressed(AActor* Actor) override;

	UFUNCTION()
	virtual void OnCharacterMouseReleased(AActor* Actor) override;
	
	// ItemCheckInfo

public:
	virtual void Tick(float DeltaTime) override;
};
