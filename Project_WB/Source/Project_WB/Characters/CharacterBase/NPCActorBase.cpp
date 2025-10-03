
#include "NPCActorBase.h"

#include "API_DebugUtils.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

ANPCActorBase::ANPCActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCActorBase::BeginPlay()
{
	Super::BeginPlay();

	MouseInteractionComponent->OnMouseOverEvent.AddDynamic(this, &ANPCActorBase::OnCharacterMouseOver);
	MouseInteractionComponent->OnMouseExitEvent.AddDynamic(this, &ANPCActorBase::OnCharacterMouseExit);
	MouseInteractionComponent->OnMouseClickEvent.AddDynamic(this, &ANPCActorBase::OnCharacterMousePressed);
	MouseInteractionComponent->OnMouseReleaseEvent.AddDynamic(this, &ANPCActorBase::OnCharacterMouseReleased);
}

void ANPCActorBase::OnCharacterMouseOver(AActor* Actor)
{
	Super::OnCharacterMouseOver(Actor);
}

void ANPCActorBase::OnCharacterMouseExit(AActor* Actor)
{
	Super::OnCharacterMouseExit(Actor);
}

void ANPCActorBase::OnCharacterMousePressed(AActor* Actor)
{
	Super::OnCharacterMousePressed(Actor);
}

void ANPCActorBase::OnCharacterMouseReleased(AActor* Actor)
{
	Super::OnCharacterMouseReleased(Actor);
}

void ANPCActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

