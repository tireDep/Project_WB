
#include "ItemBase.h"

#include "API_DebugUtils.h"
#include "Project_WB/Subsystems/ItemManagerSubsystem.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("RootBoxComponent"));
	RootComponent = RootBoxComponent;

	// todo : 필드 배치 이미지 수정 필요
	ItemFieldSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CharacterSprite"));
	ItemFieldSprite->SetupAttachment(RootBoxComponent);

	MouseInteractionComponent = CreateDefaultSubobject<UMouseInteractionComponent>(TEXT("MouseInteractionComponent"));
	MouseInteractionComponent->SetTargetSprite(ItemFieldSprite);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	UItemManagerSubsystem* ItemManger = GetGameInstance()->GetSubsystem<UItemManagerSubsystem>();
	if ( ItemManger == nullptr )
		return;

	// 테이블 데이터 세팅
	const FItemTableData* ItemTableData = ItemManger->GetItemTableData( ItemData.ItemID ); 
	if ( ItemTableData == nullptr )
	{
		FAPI_DebugUtils::ShowError("Item LoadFail! ItemName : " + ItemData.ItemName.ToString() + "ItmeID : " + FString::FromInt(ItemData.ItemID) );
		return;
	}

	ItemData = *ItemTableData;
}

UUIManagerSubsystem* AItemBase::GetUISubsystem() const
{
	if ( UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		return GameInstance->GetSubsystem<UUIManagerSubsystem>();
	}
	return nullptr;
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
