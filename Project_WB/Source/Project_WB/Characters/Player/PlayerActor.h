
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "PlayerActor.generated.h"

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

private:
	// iteninfo
	// playercontroller
};
