#pragma once

#include "CoreMinimal.h"
#include "UIWidgetBase.h"
#include "ItemNoteWidget.generated.h"

enum class EItemCategory : uint8;
class UImage;
class UTextBlock;
class UButton;

USTRUCT()
struct FGainedItemIDs
{
	// TMap Value 저장용 구조체
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<int> ItemIDs;
};

UCLASS()
class PROJECT_WB_API UItemNoteWidget : public UUIWidgetBase
{
	GENERATED_BODY()

public:
	UItemNoteWidget(const FObjectInitializer& ObjectInitializer);

	// 아이템 버튼 선택시_아이템 정보 업데이트
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnItemButtonClicked();

	// 카테고리 버튼 선택시_카테고리 업데이트
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnCategoryButtonClicked();

	// 닫기 버튼 선택시_UI 닫기
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnCloseButtonClicked();
	
	// 이전 페이지 버튼 선택시_이전 페이지 이동
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnPrevPageButtonClicked();
	
	// 다음 페이지 버튼 선택시_다음 페이지 이동
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnNextPageButtonClicked();

	// 제시하기 버튼 선택시_NPC 제시 처리
	UFUNCTION(BlueprintCallable, Category="ItemNote")
	void OnSuggestButtonClicked();

protected:
	// UI 표시 될 때 호출 함수
	virtual void OnShow_Implementation() override;

	// UI 끌 때 호출 함수
	virtual void OnHide_Implementation() override;
	
	// 초기화 시 호출 함수
	virtual void OnInitialize_Implementation() override;

	// 전체 UI 업데이트
	void UpdateAllWidget();

	// 아이템 세부 정보 업데이트
	void UpdateItemDetailInfo();

	// 아이템 페이지 업데이트
	void UpdateItemPage();

	// 위젯 바인딩(UMG 에디터에서 생성한 컴포넌트)
	// 닫기 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	// 아이템 정보 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* ItemInfoImage;

	// 아이템 정보 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemInfoText;

	// 이전 페이지 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* PrevPageButton;
	
	// 다음 페이지 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* NextPageButton;
	
	// 페이지 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PageText;

	// 제시하기 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* SuggestButton;

private:
	// 아이템 버튼들
	UPROPERTY(meta = (BindWidget))
	TArray<UButton*> ItemButtons;

	// 카테고리 버튼들
	UPROPERTY(meta = (BindWidget))
    TArray<UButton*> CategoryButtons;

	// 카테고리 배경 이미지들
	UPROPERTY(meta = (BindWidget))
	TArray<UImage*> CategoryExpandedImages;

	// 보유한 아이템 정보
	UPROPERTY()
	TMap<EItemCategory, FGainedItemIDs> ItemList;

	// 최대 페이지 수
	UPROPERTY()
	int MaxPage;

	// 현재 위치한 페이지
	UPROPERTY()
	int CurrentPage;

	// 현재 선택한 아이템
	UPROPERTY()
	int CurrentSelectItemID;
	
	// 현재 선택한 카테고리
	UPROPERTY()
	EItemCategory CurrentSelectItemCategory;
};