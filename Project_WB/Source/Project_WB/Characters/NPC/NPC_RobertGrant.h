// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_WB/Characters/CharacterBase/NPCActorBase.h"
#include "NPC_RobertGrant.generated.h"

UCLASS()
class PROJECT_WB_API ANPC_RobertGrant : public ANPCActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANPC_RobertGrant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
