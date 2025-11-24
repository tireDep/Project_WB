
#include "StringManagerSubsystem.h"
#include "API_DebugUtils.h"

UStringManagerSubsystem::UStringManagerSubsystem()
{

}

// 초기화
void UStringManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadAll_TextTable();
}

// 초기화 해제
void UStringManagerSubsystem::Deinitialize()
{
	ScriptTableData.Empty();
	
	Super::Deinitialize();
}

// 전체 대사, 대화 테이블 로드
bool UStringManagerSubsystem::LoadAll_TextTable()
{
	bool bResult = true;
	if ( LoadScriptTable() == false )
	{
		bResult = false;
	}

	if ( LoadDialogueTable() == false )
	{
		bResult = false;
	}
	
	return bResult;
}

// 캐릭터별 대사 로드
bool UStringManagerSubsystem::LoadScriptTable()
{
	ScriptTableData.Empty();

	// DefaultGame.ini에 작성된 파일명으로 로드
	for (int Index = 0; Index < ScriptTablePaths.Num(); Index++ )
	{
		UDataTable* LoadTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(),
			nullptr,
			*ScriptTablePaths[Index].ToString())
			);
		if ( LoadTable == nullptr )
		{
			FAPI_DebugUtils::ShowError("UStringManagerSubsystem::LoadScriptTable() failed!");
			continue;
		}
	
		TArray<FScriptTableData*> AllRows;
		LoadTable->GetAllRows<FScriptTableData>(TEXT("Script_GetAllRows"), AllRows);

		for (FScriptTableData* Row : AllRows)
		{
			if ( Row == nullptr )
				continue;
		
			ScriptTableData.Add(Row->ScriptID, *Row);
		}
	}

	return true;
}

// 대화 테이블 로드
bool UStringManagerSubsystem::LoadDialogueTable()
{
	DialogueTableData.Empty();
	
	UDataTable* LoadTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(),
			nullptr,
			TEXT("/Game/DataTables/DT_DialogueTable.DT_DialogueTable"))
			);
	if ( LoadTable == nullptr )
	{
		FAPI_DebugUtils::ShowError("UStringManagerSubsystem::LoadDialogueTable() failed!");
		return false;
	}
	
	TArray<FDialogueTableData*> AllRows;
	LoadTable->GetAllRows<FDialogueTableData>(TEXT("Dialogue_GetAllRows"), AllRows);

	for (FDialogueTableData* Row : AllRows)
	{
		if ( Row == nullptr )
			continue;
		
		DialogueTableData.Add(Row->DialogueID, *Row);
	}

	return true;
}

// 대사 테이블 정보 리턴
const FScriptTableData* UStringManagerSubsystem::GetScriptTableData(int KeyScriptID)
{
	const auto FindData = ScriptTableData.Find(KeyScriptID);
	if ( FindData == nullptr )
		return nullptr;

	return FindData;
}

// 대화 테이블 정보 리턴
const FDialogueTableData* UStringManagerSubsystem::GetDialogueTableData(int KeyScriptID)
{
	const auto FindData = DialogueTableData.Find(KeyScriptID);
	if ( FindData == nullptr )
		return nullptr;

	return FindData;
}
