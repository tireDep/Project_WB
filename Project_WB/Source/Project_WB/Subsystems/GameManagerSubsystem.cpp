// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Project_WB/Characters/Player/InteractionComponent.h"
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

const TWeakObjectPtr<APlayerActor> UGameManagerSubsystem::GetPlayerActor()
{
	if (CachedPlayerActor != nullptr)
		return CachedPlayerActor;
	
	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(),APlayerActor::StaticClass());
	if (FindActor != nullptr)
		CachedPlayerActor = Cast<APlayerActor>(FindActor);

	return CachedPlayerActor;
}


void UGameManagerSubsystem::NotifyDialogueResult(const FDialogueResult& Result)
{
	if (CachedPlayerActor.IsValid() == false)
		return;

	if (UInteractionComponent* InterComp = CachedPlayerActor->GetInteractionComponent())
	{
		InterComp->HandleDialogueResult(Result);
	}
}
