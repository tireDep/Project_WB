
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/DataTables/DialogTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StringManagerSubsystem.generated.h"

UCLASS()
class PROJECT_WB_API UStringManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UStringManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	bool LoadDialogTable();

	const FDialogTableData* GetDialogTableData(int KeyIndex);

private:
	UPROPERTY()
	TMap<int, FDialogTableData> DialogTable;
};
