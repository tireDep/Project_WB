
#include "BasicItem.h"

#include "API_DebugUtils.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/Characters/CharacterBase/CharacterActorBase.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"
#include "Project_WB/Subsystems/StringManagerSubsystem.h"
#include "Project_WB/Subsystems/UIManagerSubsystem.h"
#include "Project_WB/UI/DialogueWidget.h"

ABasicItem::ABasicItem()
{
	
}

int ABasicItem::GetDialogueIndex(ECharacterID CharacterID)
{
	int ResultDialogueIndex = 0;
	auto DialogKey = DialogInfo.Find( CharacterID );
	if (DialogKey != nullptr)
		ResultDialogueIndex = *DialogKey;
		
	return ResultDialogueIndex;
}

void ABasicItem::SetDialogueTextInfo(ECharacterID CharacterID, UUserWidget* Widget)
{
	int DialogueIndex = 0;
	auto DialogKey = DialogInfo.Find( CharacterID );
	if (DialogKey != nullptr)
		DialogueIndex = *DialogKey;

	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(Widget);
	if (DialogueWidget != nullptr)
		DialogueWidget->SetDialogueText(DialogueIndex);
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
	// todo : 추후 재 확인. 블루프린트에서 생성하는 것으로 변경해둠.
	// AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(),APlayerActor::StaticClass());
	// if (FindActor == nullptr)
	// 	return;
	//
	// APlayerActor* PlayerActor = Cast<APlayerActor>(FindActor);
	// if (PlayerActor == nullptr)
	// 	return;
	//
	// int DialogKeyIndex = 0;
	// // 이미 수집한 아이템인지 체크 필요
	//
	// ECharacterID CharacterID = PlayerActor->GetCharacterID();
	// auto DialogKey = DialogInfo.Find( CharacterID );
	// if (DialogKey == nullptr)
	// {
	// 	return;	
	// }
	//
	// DialogKeyIndex = *DialogKey;
	//
	// // 대화창 열기
	// UStringManagerSubsystem* StringManager = GetGameInstance()->GetSubsystem<UStringManagerSubsystem>();
	// if ( StringManager == nullptr )
	// 	return;
	//
	// const FScriptTableData* ScriptTableData = StringManager->GetScriptTableData(DialogKeyIndex);
	// if ( ScriptTableData == nullptr )
	// 	return;	
	//
	// UUIManagerSubsystem* UIManager = GetUISubsystem();
	// if ( UIManager == nullptr )
	// 	return;
}

void ABasicItem::OnItemMouseReleased(AActor* Actor)
{
	//FAPI_DebugUtils::ShowInfo( L"--------------Item Released!" );
}

void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

