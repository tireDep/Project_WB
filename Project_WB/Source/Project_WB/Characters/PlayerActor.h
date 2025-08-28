
#pragma once

#include "CoreMinimal.h"
#include "CharacterActorBase.h"
#include "PlayerActor.generated.h"

UCLASS()
class PROJECT_WB_API APlayerActor : public ACharacterActorBase
{
	GENERATED_BODY()

public:
	APlayerActor();

protected:
	virtual void BeginPlay() override;

	// iteninfo
	// playercontroller
	
public:
	virtual void Tick(float DeltaTime) override;
};
