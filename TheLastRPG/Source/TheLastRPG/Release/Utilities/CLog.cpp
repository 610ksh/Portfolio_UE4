#include "CLog.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_, Display, All)


void CLog::Print(int32 InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::FromInt(InValue));
}

void CLog::Print(float InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, FString::SanitizeFloat(InValue));
}

void CLog::Print(const FString & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue);
}

void CLog::Print(const FVector & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void CLog::Print(const FRotator & InValue, int32 InKey, float Duration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, Duration, InColor, InValue.ToString());
}

void CLog::Log(int32 InValue)
{
	UE_LOG(LOG_, Display, L"%d", InValue);
}

void CLog::Log(float InValue)
{
	UE_LOG(LOG_, Display, L"%f", InValue);
}

void CLog::Log(const FString& InValue)
{
	UE_LOG(LOG_, Display, L"%s", *InValue);
}

void CLog::Log(const FVector& InValue)
{
	UE_LOG(LOG_, Display, L"%s", *InValue.ToString());
}

void CLog::Log(const FRotator & InValue)
{
	UE_LOG(LOG_, Display, L"%s", *InValue.ToString());
}

void CLog::Log(const UObject* InObject)
{
	FString str;
	if (!!InObject)
		str.Append(InObject->GetName());

	str.Append(!!InObject ? " Not NULL" : " NULL");
	UE_LOG(LOG_, Warning, L"%s", *str);
}

void CLog::Log(const FString& InFuncName, int32 InLineNumber)
{
	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(LOG_, Warning, L"%s", *str);
}