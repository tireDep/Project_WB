// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterActorBase.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class UMouseInteractionComponent;

UENUM(BlueprintType)
enum class ECharacterEnumType : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	Player UMETA(DisplayName = "Player"),
	NPC UMETA(DisplayName = "NPC"),
	Max UMETA(DisplayName = "Max"),
};

UCLASS()
class PROJECT_WB_API ACharacterActorBase : public AActor
{
	GENERATED_BODY()

public:
	ACharacterActorBase();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnCharacterMouseOver(AActor* Actor) {}
	virtual void OnCharacterMouseExit(AActor* Actor) {}
	virtual void OnCharacterMousePressed(AActor* Actor) {}
	virtual void OnCharacterMouseReleased(AActor* Actor) {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* RootBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* CharacterSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterInfo", meta = (Priority = -10))
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterInfo", meta = (Priority = -10))
	FText CharacterDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterInfo", meta = (Priority = -5))
	int CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterInfo")
	ECharacterEnumType CharacterEnumType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UMouseInteractionComponent* MouseInteractionComponent;
	
public:
	virtual void Tick(float DeltaTime) override;
};
