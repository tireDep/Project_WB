
#include "ItemManagerSubsystem.h"
#include "API_DebugUtils.h"

UItemManagerSubsystem::UItemManagerSubsystem()
{

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

	// 런타임에 사용 가능한 로드
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

const FItemTableData* UItemManagerSubsystem::GetItemTableData(const int ItemID) const
{
	if (ItemTable.Contains(ItemID) == true)
	{
		return const_cast<FItemTableData*>(&ItemTable[ItemID]);	
	}
	
	return nullptr;
}

int UItemManagerSubsystem::GetItemID(const int ItemID) const
{
	const FItemTableData* ItemTableData = GetItemTableData(ItemID);
	if ( ItemTableData == nullptr )
		return 0;

	return ItemTableData->GetItemID();
}

