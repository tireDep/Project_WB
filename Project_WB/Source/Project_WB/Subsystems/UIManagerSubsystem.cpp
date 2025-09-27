
#include "UIManagerSubsystem.h"

UUIManagerSubsystem::UUIManagerSubsystem()
{
}

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIManagerSubsystem::Deinitialize()
{
	// Empty
	Super::Deinitialize();
}

void UUIManagerSubsystem::RegisterUI(EUIType UIType, TSubclassOf<UUIWidgetBase> WidgetClass, const FUIConfig& OutConfig)
{
}

void UUIManagerSubsystem::SetShowUI(EUIType UIType, bool bShow, bool bForceCreate)
{
}

void UUIManagerSubsystem::HandleEscapeKey()
{
}

UUIWidgetBase* UUIManagerSubsystem::CreateUIWidget(EUIType UIType)
{
	return nullptr;
}

void UUIManagerSubsystem::AddToStack(EUIType UIType)
{
}

void UUIManagerSubsystem::RemoveFromStack(EUIType UIType)
{
}

int32 UUIManagerSubsystem::GetLayerZOrder(EUILayer UILayer) const
{
	return 0;
}
