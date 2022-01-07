#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class THELASTRPG_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutObject = asset.Object;
	}


	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, L"!!obj"); // �𸮾� Ư����ȣ !! => asset != NULL : NULL�� �ƴϸ� true�� ����

		*OutObject = obj;
	}
};