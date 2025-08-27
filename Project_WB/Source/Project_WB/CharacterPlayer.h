#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECT_WB_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterPlayer();

protected:
	virtual void BeginPlay() override;
	
	// iteninfo
	// playercontroller

public:
	virtual void Tick(float DeltaSeconds) override;
};
