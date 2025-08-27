#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

UENUM(BlueprintType)
enum class CharacterEnumType : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	Player UMETA(DisplayName = "Player"),
	NPC UMETA(DisplayName = "NPC"),
	Max UMETA(DisplayName = "Max"),
};

UCLASS()
class PROJECT_WB_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="CharacterInfo", meta = (Priority = -10))
	FText characterName;

	UPROPERTY(EditAnywhere, Category="CharacterInfo", meta = (Priority = -5))
	int characterID;

	UPROPERTY(EditAnywhere, Category="CharacterInfo")
	CharacterEnumType characterEnumType;
};
