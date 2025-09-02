// Copyright Epic Games, Inc. All Rights Reserved.

#include "DebugHelperUtilsModule.h"

#define LOCTEXT_NAMESPACE "FDebugHelperUtilsModule"

// 로그 카테고리 정의
// DEFINE_LOG_CATEGORY(LogDebugUtilsPlugin);

void FDebugHelperUtilsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Log, TEXT("DebugUtils Plugin Started"));
}

void FDebugHelperUtilsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Log, TEXT("DebugUtils Plugin Shutdown"));
}

FDebugHelperUtilsModule& FDebugHelperUtilsModule::Get()
{
	return FModuleManager::LoadModuleChecked<FDebugHelperUtilsModule>("DebugHelperUtilsModule");
}

bool FDebugHelperUtilsModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("DebugHelperUtilsModule");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDebugHelperUtilsModule, DebugHelperUtils)