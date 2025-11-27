
#include "DialogueWidget.h"

#include "API_DebugUtils.h"
#include "PaperSprite.h" 
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Project_WB/DataTables/DialogueTable.h"
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
		|| CharacterImage == nullptr
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
		CharacterImage->SetBrushFromAtlasInterface(CurScriptTableData->CachedCharacterSprite);
	
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
		// todo : 아이템 획득 처리
		ItemNoteButton->SetVisibility(ESlateVisibility::Visible);
	}

	// todo : 이거 두개 체크할 방법이 필요
	// 아이템 제시 버튼
	// 대화 종료 버튼
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
	if (CurDialogueTableData->DefaultNextDialogueID == VALUE_NUMBER_ZERO)
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

// UI 열때 , 블루프린트 추가 구현 가능
void UDialogueWidget::OnShow_Implementation()
{
	Super::OnShow_Implementation();
}

// UI 닫을 때, 블루프린트 추가 구현 가능
void UDialogueWidget::OnHide_Implementation()
{
	Super::OnHide_Implementation();
}

// UI 초기화 할 때, 블루프린트 추가 구현 가능
void UDialogueWidget::OnInitialize_Implementation()
{
	Super::OnInitialize_Implementation();

	// 다음 버튼 함수 지정
	if (NextButton != nullptr)
		NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);
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
