
#include "ItemManagerSubsystem.h"
#include "API_DebugUtils.h"

UItemManagerSubsystem::UItemManagerSubsystem()
{
	// >> 생성자에서 사용 가능한 로드
	FString ItemDataPath = TEXT("DataTable'/Game/DataTables/DT_ItemTable.DT_ItemTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemData(*ItemDataPath);
	if ( DT_ItemData.Succeeded() == false )
	{
		FAPI_DebugUtils::ShowError(L"UItemManagerSubsystem::LoadItemTable() DT_ItemTable find fail!");
	}
	// <<
}

void UItemManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadItemTable();
}

void UItemManagerSubsystem::Deinitialize()
{
	ItemTable.Empty();
	
	Super::Deinitialize();
}

bool UItemManagerSubsystem::LoadItemTable()
{
	if (ItemTable.IsEmpty() == false)
	{
		FAPI_DebugUtils::ShowError(L"UItemManagerSubsystem::LoadItemTable() already load!");
		return false;
	}

	// >> 런타임에 사용 가능한 로드
	UDataTable* LoadedTable = Cast<UDataTable>(
	StaticLoadObject(UDataTable::StaticClass(),
		nullptr,
		TEXT("/Game/DataTables/DT_ItemTable.DT_ItemTable"))
		);
	if ( LoadedTable == nullptr )
	{
		FAPI_DebugUtils::ShowError(L"UItemManagerSubsystem::LoadItemTable() DT_ItemTable find fail!");
		return false;
	}
	// <<

	ItemTable.Empty();
	TArray<FItemTableData*> AllRows;
	LoadedTable->GetAllRows<FItemTableData>(TEXT("ItemManager_GetAllRows"), AllRows);
	
	for (FItemTableData* Row : AllRows)
	{
		if (Row == nullptr)
			continue;
	
		ItemTable.Add(Row->ItemID, *Row);
		FAPI_DebugUtils::ShowInfo(L"Loaded Item Table : " + Row->ItemName.ToString());
	}
	
	return true;
}

const FItemTableData* UItemManagerSubsystem::GetItemTableData(const int32 ItemID) const
{
	if (ItemTable.Contains(ItemID) == true)
	{
		return const_cast<FItemTableData*>(&ItemTable[ItemID]);	
	}
	
	return nullptr;
}

