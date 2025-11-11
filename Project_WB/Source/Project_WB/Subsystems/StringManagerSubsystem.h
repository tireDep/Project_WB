
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/DataTables/DialogueTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StringManagerSubsystem.generated.h"

UCLASS(Config=Game) // DefaultGame.ini 사용
class PROJECT_WB_API UStringManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UStringManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	bool LoadAll_TextTable();
	bool LoadScriptTable();
	bool LoadDialogueTable();

	const FScriptTableData* GetScriptTableData(int KeyScriptID);
	const FDialogueTableData* GetDialogueTableData(int KeyScriptID);

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="String Manger")
	TArray<FSoftObjectPath> ScriptTablePaths;			// 대사 테이블 파일 경로가 저장된 변수. DefulatGame.ini에 저장된 데이터 사용
	
private:
	UPROPERTY()
	TMap<int, FScriptTableData> ScriptTableData;		// 대사 테이블 데이터, < ScriptID, FScriptTableData >

	UPROPERTY()
	TMap<int, FDialogueTableData> DialogueTableData;	// 대화 테이블 데이터, < ScriptID, FDialogueTableData >

	// 테스트용
	UPROPERTY()
	TMap<int, FDialogCondition> DialogueData;
};
