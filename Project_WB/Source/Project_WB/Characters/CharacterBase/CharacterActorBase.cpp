
#include "CharacterActorBase.h"

#include "API_DebugUtils.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

ACharacterActorBase::ACharacterActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("RootBoxComponent"));
	RootComponent = RootBoxComponent;
	
	CharacterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CharacterSprite"));
	CharacterSprite->SetupAttachment(RootBoxComponent);

	// 외곽선 처리를 위한 세팅
	CharacterSprite->SetRenderCustomDepth(true);
	CharacterSprite->CustomDepthStencilValue = 1;
	CharacterSprite->CustomDepthStencilWriteMask = ERendererStencilMask::ERSM_Default;

	MouseInteractionComponent = CreateDefaultSubobject<UMouseInteractionComponent>(TEXT("MouseInteractionComponent"));
	MouseInteractionComponent->SetTargetSprite(CharacterSprite);

	MouseInteractionComponent->ShowOutLine = true;
	MouseInteractionComponent->ChangeScale = false;
}

void ACharacterActorBase::BeginPlay()
{
	Super::BeginPlay();

	MouseInteractionComponent->OnMouseOverEvent.AddDynamic(this, &ACharacterActorBase::OnCharacterMouseOver);
	MouseInteractionComponent->OnMouseExitEvent.AddDynamic(this, &ACharacterActorBase::OnCharacterMouseExit);
}

void ACharacterActorBase::OnCharacterMouseOver(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"----------------Over Character!" );
}

void ACharacterActorBase::OnCharacterMouseExit(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"----------------Exit Character!" );
}

void ACharacterActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

