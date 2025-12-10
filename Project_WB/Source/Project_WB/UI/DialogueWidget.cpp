
#include "DialogueWidget.h"

#include "API_DebugUtils.h"
#include "InteractiveToolQueryInterfaces.h"
#include "ItemNoteWidget.h"
#include "PaperSprite.h" 
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "Project_WB/DataTables/DialogueTable.h"
#include "Project_WB/Subsystems/GameManagerSubsystem.h"
#include "Project_WB/Subsystems/StringManagerSubsystem.h"

UDialogueWidget::UDialogueWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIType = EUIType::UT_Dialogue;
}

// UI 업데이트
void UDialogueWidget::UpdateDialogueText(int DialogueIndex)
{
	UStringManagerSubsystem* StringManager = GetGameInstance()->GetSubsystem<UStringManagerSubsystem>();
	if ( StringManager == nullptr )
		return;
	
	const FDialogueTableData* CurDialogueTableData = StringManager->GetDialogueTableData(DialogueIndex);
	if (CurDialogueTableData == nullptr)
	{
		FAPI_DebugUtils::ShowError("UDialogueWidget::UpdateDialogueText() DialogueTableData not exist. DialogueID : ", DialogueIndex);
		return;
	}

	CurDialogueID = DialogueIndex;
	const FScriptTableData* CurScriptTableData = StringManager->GetScriptTableData(CurDialogueTableData->ShowScriptID);
	if ( CurScriptTableData == nullptr )
	{
		FAPI_DebugUtils::ShowError("UDialogueWidget::UpdateDialogueText() ScriptTableData not exist. DialogueID : ", DialogueIndex);
		return;
	}
	
	CurScriptID = CurScriptTableData->ScriptID;
	if ( ScriptName == nullptr
		|| ScriptDesc == nullptr
		|| CharacterImageRight == nullptr
		|| CharacterImageLeft == nullptr
		|| ScriptImage == nullptr
		|| NextButton == nullptr
		|| SuggestButton == nullptr
		|| ExitButton == nullptr
		|| ItemNoteButton == nullptr
		)
	{
		return;	
	}
	
	// 초기화
	ScriptImage->SetVisibility(ESlateVisibility::Hidden);
	ItemNoteButton->SetVisibility(ESlateVisibility::Hidden);
	SuggestButton->SetVisibility(ESlateVisibility::Hidden);
	ExitButton->SetVisibility(ESlateVisibility::Hidden);

	// 업데이트
	// 캐릭터 이미지
	if (CurScriptTableData->CachedCharacterSprite != nullptr)
	{
		UImage* NowTalkCharacter = nullptr;
		UImage* LastTalkCharacter = nullptr;
		if (CurScriptTableData->CharacterImagePosition == true )
		{
			NowTalkCharacter = CharacterImageRight;
			LastTalkCharacter = CharacterImageLeft;
		}
		else
		{
			NowTalkCharacter = CharacterImageLeft;
			LastTalkCharacter = CharacterImageRight;
		}

		// 현재 말하는 캐릭터 이미지 표시
		NowTalkCharacter->SetBrushFromAtlasInterface(CurScriptTableData->CachedCharacterSprite);
		NowTalkCharacter->SetVisibility(ESlateVisibility::Visible);
		// NowTalkCharacter->SetColorAndOpacity(FLinearColor::Gray);

		// todo : 
		// 대화하던 캐릭터가 있을 경우의 처리
		if (LastTalkCharacter->GetVisibility() != ESlateVisibility::Hidden)
		{
			LastTalkCharacter->SetBrushTintColor(FLinearColor::White);
		}
	}
	
	// 캐릭터 이름
	ScriptName->SetText( FText::FromString(CurScriptTableData->ScriptShowName) );
	
	// 캐릭터 대사
	ScriptDesc->SetText( FText::FromString(CurScriptTableData->ScriptShowDesc) );
	
	// 대사 이미지
	if (CurScriptTableData->CachedImageSprite != nullptr)
	{
		ScriptImage->SetBrushFromAtlasInterface(CurScriptTableData->CachedImageSprite);
		ScriptImage->SetVisibility(ESlateVisibility::Visible);
	}
	
	// 탐정 수첩 확인 버튼
	if (CurScriptTableData->GainItemID != 0)
	{
		ItemNoteButton->SetVisibility(ESlateVisibility::Visible);

		// 아이템 획득 처리
		if (PlayerActor != nullptr)
			PlayerActor->AddGainedItem(CurScriptTableData->GainItemID);
	}

	// 마지막 대사인 경우, 스테이트 상태에 따라 버튼 표시 제어
	if (CheckIsFinalScript(CurDialogueTableData))
	{
		// NPC와 대화중인 경우
		if (PlayerActor != nullptr && PlayerActor->GetState() == PlayerState::PS_TALKING_NPC)
		{
			// 아이템 제시 버튼
			SuggestButton->SetVisibility(ESlateVisibility::Visible);
		
			// 대화 종료 버튼
			ExitButton->SetVisibility(ESlateVisibility::Visible);	
		}
	}
}

// 다음 대화문 정보가 있는지 체크 후 업데이트
void UDialogueWidget::OnNextButtonClicked()
{
	UStringManagerSubsystem* StringManager = GetGameInstance()->GetSubsystem<UStringManagerSubsystem>();
	if ( StringManager == nullptr )
		return;
	
	const FDialogueTableData* CurDialogueTableData = StringManager->GetDialogueTableData(CurDialogueID);
	if (CurDialogueTableData == nullptr)
	{
		// error
		return;
	}

	// 다음 대사가 없을 경우, UI 끄기
	if (CheckIsFinalScript(CurDialogueTableData) == true)
	{
		SetShowUI(false);
		return;
	}

	// 캐릭터 대사 분기 체크
	int NextDialogueID = VALUE_NUMBER_ZERO;
	switch (CurDialogueTableData->ConditionType)
	{
	case EConditionType::CT_HAS_ITEM:
		{
			// todo : 조건 체크
			NextDialogueID = CurDialogueTableData->ConditionNextDialogueID;
		}
		break;
	case EConditionType::CT_PROGRESS:
		{
			// todo : 조건 체크
			NextDialogueID = CurDialogueTableData->ConditionNextDialogueID;
		}
		break;
	default:
		{
			
		}
		break;
	}

	// 분기 체크에 걸리지 않을 경우, 기본 다음 진행 대사로 설정
	if (NextDialogueID == VALUE_NUMBER_ZERO)
	{
		NextDialogueID = CurDialogueTableData->DefaultNextDialogueID;
	}

	UpdateDialogueText(NextDialogueID);
}

// NPC와의 대화에서 제시하기 버튼 선택 시
// 대화 창 위에 탐정 수첩이 '제시 상태'로 열림
void UDialogueWidget::OnSuggestButtonClicked()
{
	// todo : 대화 상태인지 체크 필요
}

// 대화 종료 버튼 선택 시
void UDialogueWidget::OnExitButtonClicked()
{
	SetShowUI(false);
}

// 탐정 수첩 버튼 선택 시
// 대화 창 위에 탐정 수첩이 '기본 상태'로 열림
void UDialogueWidget::OnItemNoteButtonClicked()
{
	UUIManagerSubsystem* UIManager = GetUISubsystem();
	if (UIManager == nullptr)
		return;

	UIManager->SetShowUI( EUIType::UT_ItemNote, true );
}

// UI 열때 , 블루프린트 추가 구현 가능
void UDialogueWidget::OnShow_Implementation()
{
	Super::OnShow_Implementation();

	if (CharacterImageRight != nullptr)
		CharacterImageRight->SetVisibility(ESlateVisibility::Hidden);

	if (CharacterImageLeft != nullptr)
		CharacterImageLeft->SetVisibility(ESlateVisibility::Hidden);
	
	UGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	if (GameManager == nullptr)
		return;

	PlayerActor = GameManager->GetPlayerActor();
}

// UI 닫을 때, 블루프린트 추가 구현 가능
void UDialogueWidget::OnHide_Implementation()
{
	Super::OnHide_Implementation();

	// 기본 상태로 변경
	if (PlayerActor != nullptr)
		PlayerActor->SetState(PlayerState::PS_IDLE);
}

// UI 초기화 할 때, 블루프린트 추가 구현 가능
void UDialogueWidget::OnInitialize_Implementation()
{
	Super::OnInitialize_Implementation();

	// 다음 버튼 함수 지정
	if (NextButton != nullptr)
		NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);

	// 아이템 제시 버튼 함수 지정
	if (SuggestButton != nullptr)
		SuggestButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnSuggestButtonClicked);
	
	// 대화 종료 버튼 함수 지정
	if (ExitButton != nullptr)
		ExitButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnExitButtonClicked);

	// 아이템 획득 시 탐정 수첩 표시 버튼 함수 지정
	if (ItemNoteButton != nullptr)
		ItemNoteButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnItemNoteButtonClicked);
}

// 포커스 획득, 블루프린트 추가 구현 가능
void UDialogueWidget::OnGaindFocus_Implementation()
{
	Super::OnGaindFocus_Implementation();
}

// 포커스 상실, 블루프린트 추가 구현 가능
void UDialogueWidget::OnLostFocus_Implementation()
{
	Super::OnLostFocus_Implementation();
}

// 마지막 대사인지 체크
bool UDialogueWidget::CheckIsFinalScript(const FDialogueTableData* PtDialogueTableData)
{
	if (PtDialogueTableData->DefaultNextDialogueID == VALUE_NUMBER_ZERO
		&& PtDialogueTableData->ConditionNextDialogueID == VALUE_NUMBER_ZERO
		)
		return true;
	
	return false;
}
