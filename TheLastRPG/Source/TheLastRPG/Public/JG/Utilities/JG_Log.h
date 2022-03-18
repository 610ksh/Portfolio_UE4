// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define JG_PrintLine() {JG_Log::Log(__FUNCTION__, __LINE__);}


class THELASTRPG_API JG_Log
{
public:
	static void Print(int32 InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FString& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float Duration = 10.0f, FColor InColor = FColor::Blue);

	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);

	static void Log(const UObject* InObject); // NULL chk, 자주 사용

	static void Log(const FString& InFuncName, int32 InLineNumber);
};
