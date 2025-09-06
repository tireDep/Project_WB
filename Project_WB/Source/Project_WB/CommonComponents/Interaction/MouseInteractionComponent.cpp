
#include "MouseInteractionComponent.h"

#include "API_DebugUtils.h"
#include "PaperSpriteComponent.h"
#include "Components/PrimitiveComponent.h"

UMouseInteractionComponent::UMouseInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	TargetSpriteComponent = nullptr;
	ShowOutLine = true;
	ChangeScale = true;
}

void UMouseInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMouseInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UMouseInteractionComponent::SetTargetSprite(UPaperSpriteComponent* PaperSpriteComponent)
{
	if ( PaperSpriteComponent == nullptr )
	{
		FAPI_DebugUtils::ShowError(L"UMouseInteractionComponent::SetTargetSprite PaperSpriteComponent is nullptr");
		return;
	}

	TargetSpriteComponent = PaperSpriteComponent;

	// sprite 콜리전 설정
	TargetSpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetSpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetSpriteComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	TargetSpriteComponent->OnBeginCursorOver.AddDynamic( this, &UMouseInteractionComponent::HandleMouseOverEvent);
	TargetSpriteComponent->OnEndCursorOver.AddDynamic( this, &UMouseInteractionComponent::HandleMouseExitEvent);
	TargetSpriteComponent->OnClicked.AddDynamic( this, &UMouseInteractionComponent::HandleMouseClickEvent);
	TargetSpriteComponent->OnReleased.AddDynamic( this, &UMouseInteractionComponent::HandleMouseReleaseEvent);
}

void UMouseInteractionComponent::HandleMouseOverEvent(UPrimitiveComponent* SelectComp)
{
	if (IsValid(SelectComp) == false)
		return;

	// >> test
	if ( ShowOutLine == true )
	{
		FAPI_DebugUtils::ShowInfo( L"Over_OutLineDraw" );
		// SelectComp->SetCustomDepthStencilValue(1);
		// SelectComp->SetRenderCustomDepth(true);	
	}

	if ( ChangeScale == true )
	{
		FAPI_DebugUtils::ShowInfo( L"Over_ChangeScale" );
	}

	// todo : TOOLTIP
	
	// <<
	
	OnMouseOverEvent.Broadcast(GetOwner());
}

void UMouseInteractionComponent::HandleMouseExitEvent(UPrimitiveComponent* SelectComp)
{
	if (IsValid(SelectComp) == false)
		return;
	
	// >> test
	// <<
	
	OnMouseExitEvent.Broadcast(GetOwner());
}

void UMouseInteractionComponent::HandleMouseClickEvent(UPrimitiveComponent* SelectComp, FKey ButtonPressed)
{
	if (IsValid(SelectComp) == false)
		return;
	
	OnMouseClickEvent.Broadcast(GetOwner());
}

void UMouseInteractionComponent::HandleMouseReleaseEvent(UPrimitiveComponent* SelectComp, FKey ButtonPressed)
{
	if (IsValid(SelectComp) == false)
		return;
	
	OnMouseReleaseEvent.Broadcast(GetOwner());
}

