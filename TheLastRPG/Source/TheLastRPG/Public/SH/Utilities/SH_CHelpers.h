#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

class THELASTRPG_API SH_CHelpers
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
		verifyf(!!obj, L"!!obj"); // 언리얼 특수기호 !! => asset != NULL : NULL이 아니면 true가 나옴

		*OutObject = obj;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}

	template<typename T> // 어느 액터, 부착할 컴포넌트 종류, 변수명, 씬 컴포넌트
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent) // 있다면
		{
			(*InComponent)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent(*InComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** InComponent, FName InName)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static void FindActors(class UWorld* InWorld, TArray<T*>& OutActors)
	{
		OutActors.Empty();

		TArray<AActor*> actors;
		// T유형을 모두다 찾아와서 Actor 타입으로 actor에 기록함.
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		for (AActor* actor : actors)
			OutActors.Add(Cast<T>(actor)); // 그걸 다시 T형으로 캐스팅해서 넘겨줌.
	}
};