// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Utilities/JG_Log.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(JG_GameProject, Display, All)


void JG_Log::Print(int32 InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::FromInt(InValue));
}


void JG_Log::Print(float InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::SanitizeFloat(InValue));
}

void JG_Log::Print(const FString& InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue);
}

void JG_Log::Print(const FVector& InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void JG_Log::Print(const FRotator& InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void JG_Log::Log(int32 InValue)
{
	UE_LOG(JG_GameProject, Display, L"%d", InValue);
}

void JG_Log::Log(float InValue)
{
	UE_LOG(JG_GameProject, Display, L"%f", InValue);
}

void JG_Log::Log(const FString& InValue)
{
	UE_LOG(JG_GameProject, Display, L"%s", *InValue);
}

void JG_Log::Log(const FVector& InValue)
{
	UE_LOG(JG_GameProject, Display, L"%s", *InValue.ToString());
}

void JG_Log::Log(const FRotator& InValue)
{
	UE_LOG(JG_GameProject, Display, L"%s", *InValue.ToString());
}

void JG_Log::Log(const UObject* InObject)
{
	FString str;
	if (!!InObject)
		str.Append(InObject->GetName()); //+=도 되지만 강사는 사용하지 않음
	//str += InObject->GetName();

	str.Append(!!InObject ? " Not NULL" : " Null");
	UE_LOG(JG_GameProject, Display, L"%s", *str);
}

void JG_Log::Log(const FString& InFuncName, int32 InLineNumber)
{
	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(JG_GameProject, Display, L"%s", *str);
}