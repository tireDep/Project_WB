
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/DataTables/ItemTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemManagerSubsystem.generated.h"

UCLASS()
class PROJECT_WB_API UItemManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UItemManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	bool LoadItemTable();

	// 사용자 정의 구조체를 에디터에 노출시킬때 에러 발생
	// UFUNCTION(BlueprintGetter, Category = "Item Manager")
	const FItemTableData* GetItemTableData(const int32 ItemID) const;
	
private:
	UPROPERTY()
	TMap<int32, FItemTableData> ItemTable;
};
