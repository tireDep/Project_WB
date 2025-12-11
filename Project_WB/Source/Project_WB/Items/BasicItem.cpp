
#include "BasicItem.h"

#include "API_DebugUtils.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"
#include "Project_WB/Subsystems/GameManagerSubsystem.h"
#include "Project_WB/Subsystems/StringManagerSubsystem.h"
#include "Project_WB/Subsystems/UIManagerSubsystem.h"
#include "Project_WB/UI/DialogueWidget.h"

ABasicItem::ABasicItem()
{
	
}

// 
int ABasicItem::GetDialogueIndex(ECharacterID CharacterID)
{
	int ResultDialogueIndex = 0;
	auto DialogKey = DialogInfo.Find( CharacterID );
	if (DialogKey != nullptr)
		ResultDialogueIndex = *DialogKey;
		
	return ResultDialogueIndex;
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

// 아이템 선택시, 실행 되는 함수
void ABasicItem::OnItemMouseClick(AActor* Actor)
{
	UGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	if (GameManager == nullptr)
		return;
		
	APlayerActor* PlayerActor = GameManager->GetPlayerActor();
	if (PlayerActor == nullptr)
		return;
		
	// 플레이어 상태 변경
	PlayerActor->SetState(PlayerState::PS_TALKING_ITEM);
	
	// 이미 수집한 아이템인지 체크
	if (PlayerActor->CheckGainedItemInfo(this->ItemID) == true)
		return;
	
	ECharacterID CharacterID = PlayerActor->GetCharacterID();
	auto DialogKey = DialogInfo.Find( CharacterID );
	if (DialogKey == nullptr)
		return;
	
	// 대화창 열기
	int DialogKeyIndex = *DialogKey;
	UUIManagerSubsystem* UIManager = GetUISubsystem();
	if ( UIManager == nullptr )
		return;

	UIManager->SetShowUI(EUIType::UT_Dialogue, true);
	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(UIManager->GetUIWidget(EUIType::UT_Dialogue));
	if (DialogueWidget != nullptr)
		DialogueWidget->UpdateDialogueText(DialogKeyIndex);
}

void ABasicItem::OnItemMouseReleased(AActor* Actor)
{
	//FAPI_DebugUtils::ShowInfo( L"--------------Item Released!" );
}

void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

