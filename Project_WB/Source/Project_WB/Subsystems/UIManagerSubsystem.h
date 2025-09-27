
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/UI/UITypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Systems/MovieSceneBlenderSystemHelper.h"
#include "UIManagerSubsystem.generated.h"

class UUIWidgetBase;

USTRUCT()
struct FUIWidgetInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UUIWidgetBase> WidgetClass;

	UPROPERTY()
	UUIWidgetBase* Widget;

	FUIConfig UIConfig;

	FUIWidgetInfo()
	{
		Init();
	}

	void Init()
	{
		Widget = nullptr;
		WidgetClass = nullptr;
		UIConfig.Init();
	}
};

UCLASS()
class PROJECT_WB_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="UI Manager")
	void RegisterUI(EUIType UIType, TSubclassOf<UUIWidgetBase> WidgetClass, const FUIConfig& OutConfig);

	UFUNCTION(BlueprintCallable, Category="UI Manager")
	void SetShowUI(EUIType UIType, bool bShow, bool bForceCreate = false);

	// UFUNCTION(BlueprintCallable, Category="UI Manager")
	// void HideAllUI(const TArray<EUIType>& ExceptTypes = TArray<EUIType>());

	UFUNCTION(BlueprintCallable, Category="UI Manager")
	void HandleEscapeKey();

protected:
	UPROPERTY()
	TMap<EUIType, FUIWidgetInfo> RegisteredUIs;	// 등록된 UI 정보

	UPROPERTY()
	TArray<EUIType> UIStack;	// 현재 열린 UI들의 스택
	
private:
	UUIWidgetBase* CreateUIWidget(EUIType UIType);
	void AddToStack(EUIType UIType);
	void RemoveFromStack(EUIType UIType);
	int32 GetLayerZOrder(EUILayer UILayer) const;
};
