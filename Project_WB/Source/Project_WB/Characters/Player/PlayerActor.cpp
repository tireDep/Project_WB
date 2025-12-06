
#include "PlayerActor.h"

APlayerActor::APlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = PlayerState::PS_IDLE;
}

void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

