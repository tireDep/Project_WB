
#include "DialogueWidget.h"

#include "Components/TextBlock.h"
#include "Project_WB/Subsystems/StringManagerSubsystem.h"

UDialogueWidget::UDialogueWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIType = EUIType::UT_Dialogue; 
}

// UI 업데이트
void UDialogueWidget::SetDialogueText(int DialogueIndex)
{
	UStringManagerSubsystem* StringManager = GetGameInstance()->GetSubsystem<UStringManagerSubsystem>();
	if ( StringManager == nullptr )
		return;

	const FScriptTableData* ScriptTableData = StringManager->GetScriptTableData(DialogueIndex);
	if ( ScriptTableData == nullptr )
	{
		//error
		return;
	}

	if ( ScriptName == nullptr
		|| ScriptDesc == nullptr )
		return;
	
	// 초기화

	// 업데이트
	// * 캐릭터 대사 분기문 적용 필요
	// 캐릭터 이미지
	// 캐릭터 이름
	ScriptName->SetText( FText::FromString(ScriptTableData->ScriptShowName) );
	
	// 캐릭터 대사
	ScriptDesc->SetText( FText::FromString(ScriptTableData->ScriptDesc) );
	
	// 대사 이미지
	// 대사 버튼 표시
	// - 다음
	// - 탐정 수첩_아이템 획득 
	// - 탐정 수첩_아이템 제시
	// - 대화 종료
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
