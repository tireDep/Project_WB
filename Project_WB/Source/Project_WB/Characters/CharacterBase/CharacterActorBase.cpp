
#include "CharacterActorBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ACharacterActorBase::ACharacterActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionCollision = CreateDefaultSubobject<UBoxComponent>(FName("InteractionCollision"));
	RootComponent = InteractionCollision;
	
	CharacterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CharacterSprite"));
	CharacterSprite->SetupAttachment(InteractionCollision);
}

void ACharacterActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

