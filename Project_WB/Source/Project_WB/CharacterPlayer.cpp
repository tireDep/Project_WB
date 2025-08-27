
#include "CharacterPlayer.h"

ACharacterPlayer::ACharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
