
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManagerSubsystem.generated.h"

class APlayerActor;

UCLASS()
class PROJECT_WB_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGameManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const TWeakObjectPtr<APlayerActor> GetPlayerActor();

	void NotifyDialogueResult(const FDialogueResult& Result);

private:
	TWeakObjectPtr<APlayerActor> CachedPlayerActor;
};
