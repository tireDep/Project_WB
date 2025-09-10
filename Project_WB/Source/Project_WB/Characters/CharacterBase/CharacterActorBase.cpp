
#include "CharacterActorBase.h"

#include "API_DebugUtils.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

ACharacterActorBase::ACharacterActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("RootBoxComponent"));
	RootComponent = RootBoxComponent;
	
	CharacterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CharacterSprite"));
	CharacterSprite->SetupAttachment(RootBoxComponent);

	MouseInteractionComponent = CreateDefaultSubobject<UMouseInteractionComponent>(TEXT("MouseInteractionComponent"));
	MouseInteractionComponent->SetTargetSprite(CharacterSprite);
}

void ACharacterActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

