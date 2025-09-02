#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

// 클래스에 MODULE_API 매크로 적용 필오
// DEBUGHELPERUTILS_API는 UE가 DebugHelperUtils 모듈용으로 자동 생성하는 export/import 매크로
class DEBUGHELPERUTILS_API FAPI_DebugUtils
{
public:
	// 에러 메시지를 화면과 로그에 출력
	static void ShowError(const FString& ErrorMessage, float Duration = 10.0f);

	// 경고 메시지를 화면과 로그에 출력
	static void ShowWarning(const FString& WarningMessage, float Duration = 10.0f);

	// 정보 메시지를 화면과 로그에 출력
	static void ShowInfo(const FString& InfoMessage, float Duration = 10.0f);

	// 성공 메시지를 화면과 로그에 출력
	static void ShowSuccess(const FString& SuccessMessage, float Duration = 10.0f);

	// 포맷 문자열을 사용한 에러 출력
	template<typename... Args>
	static void ShowErrorf(const TCHAR* Format, Args... args)
	{
		ShowError(FString::Printf(Format, args...));
	}

	// 포맷 문자열을 사용한 경고 출력
	template<typename... Args>
	static void ShowWarningf(const TCHAR* Format, Args... args)
	{
		ShowWarning(FString::Printf(Format, args...));
	}

	// 포맷 문자열을 사용한 정보 출력
	template<typename... Args>
	static void ShowInfof(const TCHAR* Format, Args... args)
	{
		ShowInfo(FString::Printf(Format, args...));
	}

	// 플러그인 활성화 상태 체크
	static bool IsPluginAvailable();

private:
	// 내부 메시지 출력 함수
	static void OutputMessage(const FString& Message, const FColor& Color, const FString& MsgLogType, float Duration);
};