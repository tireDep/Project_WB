
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
	const FItemTableData* GetItemTableData(const int ItemID) const;

	// todo :
	// 직접 노출시킬 수 없어, 필요한값만 노출 시키는 함수로 래핑
	UFUNCTION(BlueprintGetter, Category = "Item Manager")
	int GetItemID(const int ItemID) const;
	
private:
	UPROPERTY()
	TMap<int32, FItemTableData> ItemTable;
};
