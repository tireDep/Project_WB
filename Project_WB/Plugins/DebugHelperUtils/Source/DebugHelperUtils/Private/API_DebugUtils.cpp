#include "API_DebugUtils.h"
#include "DebugHelperUtilsModule.h"

void FAPI_DebugUtils::ShowError(const FString& ErrorMessage, float Duration)
{
	OutputMessage(ErrorMessage, FColor::Red, TEXT("ERROR"), Duration);
}

void FAPI_DebugUtils::ShowWarning(const FString& WarningMessage, float Duration)
{
	OutputMessage(WarningMessage, FColor::Yellow, TEXT("WARNING"), Duration);
}

void FAPI_DebugUtils::ShowInfo(const FString& InfoMessage, float Duration)
{
	OutputMessage(InfoMessage, FColor::Blue, TEXT("INFO"), Duration);
}

void FAPI_DebugUtils::ShowSuccess(const FString& SuccessMessage, float Duration)
{
	OutputMessage(SuccessMessage, FColor::Green, TEXT("SUCCESS"), Duration);
}

bool FAPI_DebugUtils::IsPluginAvailable()
{
	return FDebugHelperUtilsModule::IsAvailable();
}

void FAPI_DebugUtils::OutputMessage(const FString& Message, const FColor& Color, const FString& MsgLogType, float Duration)
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
#endif

	if (MsgLogType == TEXT("ERROR"))
	{
		UE_LOG(LogTemp, Error, TEXT("[DebugUtils] %s"), *Message);
	}
	else if (MsgLogType == TEXT("WARNING"))
	{
		UE_LOG(LogTemp, Warning, TEXT("[DebugUtils] %s"), *Message);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[DebugUtils] %s"), *Message);
	}
}
