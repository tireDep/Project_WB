
#include "Blueprint/UserWidget.h"
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
