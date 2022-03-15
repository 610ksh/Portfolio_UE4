#include "SH/Utilities/SH_CLog.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_SH, Display, All)


void SH_CLog::Print(int32 InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::FromInt(InValue));
}

void SH_CLog::Print(float InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::SanitizeFloat(InValue));
}

void SH_CLog::Print(const FString & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue);
}

void SH_CLog::Print(const FVector & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void SH_CLog::Print(const FRotator & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void SH_CLog::Log(int32 InValue)
{
	UE_LOG(LOG_SH, Display, L"%d", InValue);
}

void SH_CLog::Log(float InValue)
{
	UE_LOG(LOG_SH, Display, L"%f", InValue);
}

void SH_CLog::Log(const FString& InValue)
{
	UE_LOG(LOG_SH, Display, L"%s", *InValue);
}

void SH_CLog::Log(const FVector& InValue)
{
	UE_LOG(LOG_SH, Display, L"%s", *InValue.ToString());
}

void SH_CLog::Log(const FRotator & InValue)
{
	UE_LOG(LOG_SH, Display, L"%s", *InValue.ToString());
}

void SH_CLog::Log(const UObject* InObject)
{
	FString str;
	if (!!InObject)
		str.Append(InObject->GetName());

	str.Append(!!InObject ? " Not NULL" : " NULL");
	UE_LOG(LOG_SH, Warning, L"%s", *str);
}

void SH_CLog::Log(const FString& InFuncName, int32 InLineNumber)
{
	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(LOG_SH, Warning, L"%s", *str);
}