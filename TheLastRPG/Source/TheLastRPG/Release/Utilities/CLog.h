#pragma once

#include "CoreMinimal.h"

#define PrintLine() {CLog::Log(__FUNCTION__, __LINE__);}

class THELASTRPG_API CLog
{
public:
	/// Print viewport (Screen)
	static void Print(int32 InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FString& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);

	/// Print log
	static void Log(int32 InValue, bool Verbosity = false);
	static void Log(float InValue, bool Verbosity = false);
	static void Log(const FString& InValue, bool Verbosity = false);
	static void Log(const FVector& InValue, bool Verbosity = false);
	static void Log(const FRotator& InValue, bool Verbosity = false);

	static void Log(const UObject* InObject, bool Verbosity = false);
	static void Log(const FString& InFuncName, int32 InLineNumber, bool Verbosity = false);

};
