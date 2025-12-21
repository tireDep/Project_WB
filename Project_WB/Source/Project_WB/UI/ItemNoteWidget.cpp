
#include "ItemNoteWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Project_WB/Characters/Player/PlayerActor.h"
#include "Project_WB/DataTables/DialogueTable.h"
#include "Project_WB/DataTables/ItemTable.h"
#include "Project_WB/Subsystems/GameManagerSubsystem.h"
#include "Project_WB/Subsystems/ItemManagerSubsystem.h"

UItemNoteWidget::UItemNoteWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UIType = EUIType::UT_ItemNote;

	ItemList.Empty();
	MaxPage = VALUE_NUMBER_ZERO;
	CurrentPage = VALUE_NUMBER_ZERO;
	CurrentSelectItemID = VALUE_NUMBER_ZERO;
	CurrentSelectItemCategory = EItemCategory::IC_INVALID;
}

// 아이템 버튼 선택 시 호출 함수
void UItemNoteWidget::OnItemButtonClicked()
{
	UpdateItemDetailInfo();
}

// 카테고리 버튼 선택 시 호출 함수
void UItemNoteWidget::OnCategoryButtonClicked()
{
	UpdateItemPage();
}

// 닫기 버튼 선택 시 호출 함수
void UItemNoteWidget::OnCloseButtonClicked()
{
	SetShowUI(false);
}

// 이전 페이지 버튼 선택 시 호출 함수
void UItemNoteWidget::OnPrevPageButtonClicked()
{
	// 첫번째 페이지일 경우, 처리하지 않음
	if (CurrentPage <= VALUE_NUMBER_ZERO)
		return;

	CurrentPage--;
	UpdateItemPage();
}

// 다음 페이지 버튼 선택 시 호출 함수
void UItemNoteWidget::OnNextPageButtonClicked()
{
	// 최대 페이지일 경우, 처리하지 않음
	if (MaxPage <= CurrentPage + 1)
		return;
	
	CurrentPage++;
	UpdateItemPage();
}

// 제시하기 버튼 선택 시 호출 함수
void UItemNoteWidget::OnSuggestButtonClicked()
{
}

// UI 표시 될 때 호출 함수
void UItemNoteWidget::OnShow_Implementation()
{
	Super::OnShow_Implementation();

	UItemManagerSubsystem* ItemManager = GetGameInstance()->GetSubsystem<UItemManagerSubsystem>();
	if (ItemManager == nullptr)
		return;
	
	UGameManagerSubsystem* GM = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	if (GM == nullptr)
		return;

	const TWeakObjectPtr<APlayerActor> PlayerActor = GM->GetPlayerActor();
	if (PlayerActor == nullptr)
		return;

	const TArray<FItemInformation> ItemInfos = PlayerActor->GetGainedItems();
	if (ItemInfos.Num() < 0)
		return;

	// 아이템 리스트 생성
	ItemList.Empty();
	for (FItemInformation ItemInfo : ItemInfos)
	{
		const FItemTableData* ItemTableData = ItemManager->GetItemTableData(ItemInfo.ItemID);
		if (ItemTableData == nullptr)
			continue;

		auto findIter = ItemList.Find(ItemTableData->ItemCategory);
		if (findIter != nullptr)
		{
			// 저장되어 있어, 기존 값에 추가
			findIter->ItemIDs.Add(ItemTableData->ItemID);
		}
		else
		{
			// 저장되어 있지 않아, 새로 저장
			FGainedItemIDs GainedItemID;
			GainedItemID.ItemIDs.Add(ItemTableData->ItemID);
		
			ItemList.Add(ItemTableData->ItemCategory, GainedItemID);
		}
	}

	// 데이터 초기화
	CurrentPage = VALUE_NUMBER_ZERO;
	CurrentSelectItemID = VALUE_NUMBER_ZERO;
	CurrentSelectItemCategory = EItemCategory::IC_BASIC;

	// 최대 페이지 수 계산
	auto SelectIter = ItemList.Find(CurrentSelectItemCategory);
	if (SelectIter == nullptr || SelectIter->ItemIDs.Num() == 0)
		return;
	
	MaxPage = SelectIter->ItemIDs.Num() % ItemButtons.Num();
	
	UpdateAllWidget();
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

	if (SuggestButton != nullptr)
		SuggestButton->OnClicked.AddDynamic(this, &UItemNoteWidget::OnSuggestButtonClicked);
}

// 전체 UI 업데이트
void UItemNoteWidget::UpdateAllWidget()
{
	UpdateItemPage();
	UpdateItemDetailInfo();
}

// 선택한 아이템 정보 업데이트
void UItemNoteWidget::UpdateItemDetailInfo()
{
	// if (CurrentSelectItemID == VALUE_NUMBER_ZERO)
	// 	return;
}

// 아이템 페이지 업데이트
void UItemNoteWidget::UpdateItemPage()
{
	UItemManagerSubsystem* ItemManager = GetGameInstance()->GetSubsystem<UItemManagerSubsystem>();
	if (ItemManager == nullptr)
		return;
	
	FGainedItemIDs* GainedItemIDs = ItemList.Find(CurrentSelectItemCategory);
	if (GainedItemIDs == nullptr || GainedItemIDs->ItemIDs.Num() == 0)
		return;
	
	// UI 초기화
	// 아이템 버튼 끄기
	for (UButton* ItemButton : ItemButtons)
	{
		if (ItemButton == nullptr)
			continue;

		ItemButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	// UI 업데이트
	int MaxItemButtonsCount	= ItemButtons.Num();	// UI 아이템 버튼 수
	int PassItemCount		= CurrentPage * MaxItemButtonsCount;	// 페이지 수에 따른 패스할 아이템 수
	int NowPassCount		= VALUE_NUMBER_ZERO;	// 현재 패스한 아이템 수
	int NowButtonIndex		= VALUE_NUMBER_ZERO;	// 현재 업데이트하는 버튼 인덱스
	// 아이템 버튼 정보 업데이트
	for (int ItemID : GainedItemIDs->ItemIDs)
	{
		// 버튼 모두 업데이트 시 완료
		if (NowButtonIndex > MaxItemButtonsCount)
			break;
		
		if (NowPassCount < PassItemCount)
		{
			NowPassCount++;
			continue;
		}

		const FItemTableData* ItemTableData = ItemManager->GetItemTableData(ItemID);
		if (ItemTableData == nullptr)
			continue;

		TWeakObjectPtr<UButton> Button = ItemButtons[NowButtonIndex];
		if (Button == nullptr)
			continue;

		Button->SetVisibility(ESlateVisibility::Visible);
		// 이미지 설정
		// 값 설정
		Button->SetBackgroundColor(FColor::Green);	// todo : 테스트용

		NowButtonIndex++;
	}
	
	// 페이지 업데이트
	if (PageText != nullptr)
	{
		// FString PageString = FString::Printf(
		// 	   TEXT("%d / %d"),
		// 	   CurrentPage,
		// 	   MaxPage
		//    );
		
		PageText->SetText(
			FText::Format(
				FText::FromString(TEXT("{0} / {1}")),
				FText::AsNumber(CurrentPage + 1),
				FText::AsNumber(MaxPage)
				)
			);
	}
	
	// 카테고리 업데이트

	// 제시하기 버튼
	// bool 멤버 변수 추가 필요
}
