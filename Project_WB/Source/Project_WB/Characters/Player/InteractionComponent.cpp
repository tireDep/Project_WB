#include "InteractionComponent.h"

#include "PlayerActor.h"
#include "Project_WB/DataTables/DialogueTable.h"
#include "Project_WB/UI/DialogueWidget.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// 대화 UI 플레이어 로직 처리
void UInteractionComponent::HandleDialogueResult(const FDialogueResult& Result)
{
	APlayerActor* PlayerActor = Cast<APlayerActor>(GetOwner());
	if (PlayerActor == nullptr)
		return;

	// 아이템 획득
	if (Result.GainItemID != VALUE_NUMBER_ZERO)
	{
		PlayerActor->AddGainedItem(Result.GainItemID);
	}

	// 상태 변경
	if (Result.ChangeState != EPlayerState::PS_INVALID)
	{
		PlayerActor->SetState(Result.ChangeState);
	}
}
