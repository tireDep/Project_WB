
#include "ItemBase.h"

#include "API_DebugUtils.h"
#include "Project_WB/Subsystems/ItemManagerSubsystem.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Project_WB/CommonComponents/Interaction/MouseInteractionComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("RootBoxComponent"));
	RootComponent = RootBoxComponent;
	
	ItemSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CharacterSprite"));
	ItemSprite->SetupAttachment(RootBoxComponent);

	MouseInteractionComponent = CreateDefaultSubobject<UMouseInteractionComponent>(TEXT("MouseInteractionComponent"));
	MouseInteractionComponent->SetTargetSprite(ItemSprite);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	UItemManagerSubsystem* ItemManger = GetGameInstance()->GetSubsystem<UItemManagerSubsystem>();
	if ( ItemManger == nullptr )
		return;

	// 테이블 데이터 세팅
	const FItemTableData* ItemTableData = ItemManger->GetItemTableData( ItemID ); 
	if ( ItemTableData == nullptr )
	{
		FAPI_DebugUtils::ShowError("Item LoadFail! ItemName : " + ItemName.ToString() + "ItmeID : " + FString::FromInt(ItemID) );
		return;
	}
	
	ItemID = ItemTableData->ItemID;
	ItemName = ItemTableData->ItemName;
	ItemDescription = ItemTableData->ItemDescription;
	DialogInfo = ItemTableData->DialogInfo;
	ItemSprite->SetSprite(ItemTableData->ItemSprite);
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
