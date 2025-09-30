
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
	// FString DataPath = TEXT("DataTable'/Game/DataTables/DT_DialogTable.DT_DialogTable");
	
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
		FAPI_DebugUtils::ShowInfo(L"Loaded Data Table : " + Row->GetDialogID());
	}

	return true;
}
