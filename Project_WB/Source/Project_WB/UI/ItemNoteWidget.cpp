
#include "ItemNoteWidget.h"

UItemNoteWidget::UItemNoteWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIType = EUIType::UT_ItemNote;
}

// UI 표시 될 때 호출 함수
void UItemNoteWidget::OnShow_Implementation()
{
	Super::OnShow_Implementation();
}

// UI 끌 때 호출 함수
void UItemNoteWidget::OnHide_Implementation()
{
	Super::OnHide_Implementation();
}

// 초기화 시 호출 함수
void UItemNoteWidget::OnInitialize_Implementation()
{
	Super::OnInitialize_Implementation();
}
