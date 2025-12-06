// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Project_WB/Characters/Player/PlayerActor.h"

UGameManagerSubsystem::UGameManagerSubsystem()
{
	
}

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGameManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

APlayerActor* UGameManagerSubsystem::GetPlayerActor()
{
	if (PlayerActor != nullptr)
		return PlayerActor;
	
	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(),APlayerActor::StaticClass());
	if (FindActor != nullptr)
		PlayerActor = Cast<APlayerActor>(FindActor);

	return PlayerActor;
}
