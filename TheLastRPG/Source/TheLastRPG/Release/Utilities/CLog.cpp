#include "CLog.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_GameProject, Display, All)

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

// Display vs Warning
void CLog::Log(int32 InValue, bool Verbosity)
{
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%d", InValue);
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%d", InValue);
	}
}

void CLog::Log(float InValue, bool Verbosity)
{
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%f", InValue);
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%f", InValue);
	}
}

void CLog::Log(const bool* InValue, bool Verbosity)
{
	if (Verbosity)
	{
		if (*InValue) { UE_LOG(LOG_GameProject, Warning, L"True"); }
		else { UE_LOG(LOG_GameProject, Warning, L"False"); }
	}
	else
	{
		if (*InValue) { UE_LOG(LOG_GameProject, Display, L"True"); }
		else { UE_LOG(LOG_GameProject, Display, L"False"); }
	}
}

void CLog::Log(const FString& InValue, bool Verbosity)
{
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%s", *InValue);
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%s", *InValue);
	}
}

void CLog::Log(const FVector& InValue, bool Verbosity)
{
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%s", *InValue.ToString());
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%s", *InValue.ToString());
	}
}

void CLog::Log(const FRotator & InValue, bool Verbosity)
{
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%s", *InValue.ToString());
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%s", *InValue.ToString());
	}
}

void CLog::Log(const UObject* InObject, bool Verbosity)
{
	FString str;
	if (!!InObject)
		str.Append(InObject->GetName());

	str.Append(!!InObject ? " Not NULL" : " NULL");
	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%s", *str);
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%s", *str);
	}
}

void CLog::Log(const FString& InFuncName, int32 InLineNumber, bool Verbosity)
{
	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	if (Verbosity)
	{
		UE_LOG(LOG_GameProject, Warning, L"%s", *str);
	}
	else
	{
		UE_LOG(LOG_GameProject, Display, L"%s", *str);
	}
}