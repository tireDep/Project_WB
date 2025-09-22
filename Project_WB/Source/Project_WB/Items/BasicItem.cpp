
#include "BasicItem.h"

#include "API_DebugUtils.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

ABasicItem::ABasicItem()
{
	
}

void ABasicItem::BeginPlay()
{
	Super::BeginPlay();

	MouseInteractionComponent->OnMouseOverEvent.AddDynamic(this, &ABasicItem::OnItemMouseOver);
	MouseInteractionComponent->OnMouseReleaseEvent.AddDynamic(this, &ABasicItem::OnItemMouseReleased);
	MouseInteractionComponent->OnMouseClickEvent.AddDynamic(this, &ABasicItem::OnItemMouseClick);
	MouseInteractionComponent->OnMouseExitEvent.AddDynamic(this, &ABasicItem::OnItemMouseExit);
}

void ABasicItem::OnItemMouseOver(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"----------------Item MouseOver!" );
}

void ABasicItem::OnItemMouseExit(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"----------------Item MouseExit!" );
}

void ABasicItem::OnItemMouseClick(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"---------------Item Click!" );
}

void ABasicItem::OnItemMouseReleased(AActor* Actor)
{
	FAPI_DebugUtils::ShowInfo( L"--------------Item Released!" );
}

void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

