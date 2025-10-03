
#include "ItemManagerSubsystem.h"
#include "API_DebugUtils.h"
#include "DataTableEditorUtils.h"

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
	}
	
	return true;
}

// 아이템 테이블 정보 리턴
const FItemTableData* UItemManagerSubsystem::GetItemTableData(const int ItemID) const
{
	if (ItemTable.Contains(ItemID) == true)
	{
		return const_cast<FItemTableData*>(&ItemTable[ItemID]);	
	}
	
	return nullptr;
}

// 아이템 아이디 테스트용
int UItemManagerSubsystem::GetItemID(const int ItemID) const
{
	const FItemTableData* ItemTableData = GetItemTableData(ItemID);
	if ( ItemTableData == nullptr )
		return 0;

	return ItemTableData->GetItemID();
}

