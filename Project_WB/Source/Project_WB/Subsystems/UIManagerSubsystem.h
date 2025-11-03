
#pragma once

#include "CoreMinimal.h"
#include "Project_WB/UI/UITypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Systems/MovieSceneBlenderSystemHelper.h"
#include "UIManagerSubsystem.generated.h"

class UUIWidgetBase;

UCLASS()
class PROJECT_WB_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManagerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
};
