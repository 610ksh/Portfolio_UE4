#pragma once

#include "CoreMinimal.h"

#define PrintLine_SH() {SH_CLog::Log(__FUNCTION__, __LINE__);}

class THELASTRPG_API SH_CLog
{
public:
	/// 화면 출력을 위한 함수
	static void Print(int32 InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FString& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);

	/// 출력 로그를 위한 함수
	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);

	static void Log(const UObject* InObject);
	static void Log(const FString& InFuncName, int32 InLineNumber);

};
