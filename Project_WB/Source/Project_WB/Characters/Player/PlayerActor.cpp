
#include "PlayerActor.h"

APlayerActor::APlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

