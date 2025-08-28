// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamemodeVisualNovel.generated.h"

UCLASS()
class PROJECT_WB_API AGamemodeVisualNovel : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGamemodeVisualNovel();

protected:
	virtual void BeginPlay() override;
};
