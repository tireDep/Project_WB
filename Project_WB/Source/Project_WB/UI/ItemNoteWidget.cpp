
#include "ItemNoteWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"

UItemNoteWidget::UItemNoteWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIType = EUIType::UT_ItemNote;
}

// 아이템 버튼 선택 시 호출 함수
void UItemNoteWidget::OnItemButtonClicked()
{
}

// 카테고리 버튼 선택 시 호출 함수
void UItemNoteWidget::OnCategoryButtonClicked()
{
}

// 닫기 버튼 선택 시 호출 함수
void UItemNoteWidget::OnCloseButtonClicked()
{
	SetShowUI(false);
}

// 이전 페이지 버튼 선택 시 호출 함수
void UItemNoteWidget::OnPrevPageButtonClicked()
{
}

// 다음 페이지 버튼 선택 시 호출 함수
void UItemNoteWidget::OnNextPageButtonClicked()
{
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

	// 위젯에서 이름 규칙에 맞는 버튼 모두 찾기
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);

	for (UWidget* Widget : AllWidgets)
	{
		if (UButton* Button = Cast<UButton>(Widget))
		{
			if (Button->GetName().StartsWith(TEXT("ItemButton_")))
			{
				ItemButtons.Add(Button);
				int32 Index = ItemButtons.Num() - 1;	// 각각 다른 인덱스 저장
				Button->OnClicked.AddUniqueDynamic(this, &UItemNoteWidget::OnItemButtonClicked);	
			}
			else if (Button->GetName().StartsWith(TEXT("CategoryButton_")))
			{
				CategoryButtons.Add(Button);
				int32 Index = CategoryButtons.Num() - 1;	// 각각 다른 인덱스 저장
				Button->OnClicked.AddUniqueDynamic(this, &UItemNoteWidget::OnItemButtonClicked);
			}	
		}
		else if (UImage* Image = Cast<UImage>(Widget))
		{
			if (Image->GetName().StartsWith(TEXT("CategoryExpandedImage_")))
				CategoryExpandedImages.Add(Image);
		}
	}

	// 함수 지정
	if (CloseButton != nullptr)
		CloseButton->OnClicked.AddDynamic(this, &UItemNoteWidget::OnCloseButtonClicked);

	if (PrevPageButton != nullptr)
		PrevPageButton->OnClicked.AddDynamic(this, &UItemNoteWidget::OnPrevPageButtonClicked);

	if (NextPageButton != nullptr)
		NextPageButton->OnClicked.AddDynamic(this, &UItemNoteWidget::OnNextPageButtonClicked);
}
