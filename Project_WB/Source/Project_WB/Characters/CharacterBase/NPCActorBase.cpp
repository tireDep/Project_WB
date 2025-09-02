
#include "NPCActorBase.h"

ANPCActorBase::ANPCActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

