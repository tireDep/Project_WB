
#include "StringManagerSubsystem.h"

#include <string>

#include "API_DebugUtils.h"

UStringManagerSubsystem::UStringManagerSubsystem()
{

}

void UStringManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadDialogTable();
}

void UStringManagerSubsystem::Deinitialize()
{
	DialogTable.Empty();
	
	Super::Deinitialize();
}

bool UStringManagerSubsystem::LoadDialogTable()
{
	if ( DialogTable.IsEmpty() == false )
	{
		FAPI_DebugUtils::ShowError("UStringManagerSubsystem::LoadDialogTable() already load!");
		return false;
	}

	UDataTable* LoadTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(),
			nullptr,
			TEXT("/Game/DataTables/DT_DialogTable.DT_DialogTable"))
			);
	if ( LoadTable == nullptr )
	{
		FAPI_DebugUtils::ShowError("UStringManagerSubsystem::LoadDialogTable() failed!");
		return false;
	}

	DialogTable.Empty();
	TArray<FDialogTableData*> AllRows;
	LoadTable->GetAllRows<FDialogTableData>(TEXT("DialogManager_GetAllRows"), AllRows);

	for (FDialogTableData* Row : AllRows)
	{
		if ( Row == nullptr )
			continue;

		DialogTable.Add(Row->GetDialogID(), *Row);
	}

	return true;
}

// 다이얼로그 테이블 리턴
const FDialogTableData* UStringManagerSubsystem::GetDialogTableData(int KeyIndex)
{
	const auto FindData = DialogTable.Find(KeyIndex);
	if ( FindData == nullptr )
		return nullptr;

	return FindData;
}
