
#include "BasicItem.h"

#include "API_DebugUtils.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"
#include "Project_WB/Subsystems/StringManagerSubsystem.h"

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
	//FAPI_DebugUtils::ShowInfo( L"----------------Item MouseOver!" );
}

void ABasicItem::OnItemMouseExit(AActor* Actor)
{
	//FAPI_DebugUtils::ShowInfo( L"----------------Item MouseExit!" );
}

void ABasicItem::OnItemMouseClick(AActor* Actor)
{
	// todo : Actor 인자 필요한지 전체 체크 필요함..
	
	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(),APlayerActor::StaticClass());
	if (FindActor == nullptr)
		return;

	APlayerActor* PlayerActor = Cast<APlayerActor>(FindActor);
	if (PlayerActor == nullptr)
		return;

	int DialogKeyIndex = 0;
	// 대화중 체크 필요
	{
		
	}
	// 대화중이 아닐 경우
	{
		// 이미 수집한 아이템인지 체크 필요

		ECharacterID CharacterID = PlayerActor->GetCharacterID();
		auto DialogKey = DialogInfo.Find( CharacterID );
		if (DialogKey == nullptr)
		{
			// error
			return;	
		}

		DialogKeyIndex = *DialogKey;
	}

	// 수집한 아이템 정보로 저장

	// 대화창 열기
	// >>
	UStringManagerSubsystem* StringManager = GetGameInstance()->GetSubsystem<UStringManagerSubsystem>();
	if ( StringManager == nullptr )
		return;

	const FDialogTableData* DialogTableData = StringManager->GetDialogTableData(DialogKeyIndex);
	if ( DialogTableData == nullptr )
	{
		// error
		return;	
	}

	FAPI_DebugUtils::ShowInfo( DialogTableData->DialogShowName + L" : " + DialogTableData->DialogString );
	// <<
}

void ABasicItem::OnItemMouseReleased(AActor* Actor)
{
	//FAPI_DebugUtils::ShowInfo( L"--------------Item Released!" );
}

void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

