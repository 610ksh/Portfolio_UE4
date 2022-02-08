// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "YH_IRifle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UYH_IRifle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELASTRPG_API IYH_IRifle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	//순수 가상함수를 포함한 즉 인터페이스나 추상클래스로 상속받은애들은 반드시 순수가상함수로 재정의 해주지 않으면 밑의 상속받는애도 추상클래스가 되서 객체화 될수 없다.
	virtual class AYH_CRifle* GetRifle() = 0;
	virtual void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) = 0;
	//쏠수있는 지점이면 포커스를 주고(플레어이쪽에서는 크로스헤어에 대한 포커스를 주고). 쏠수있는애라면 저쪽은 먼가 처리하는 애가 들어갈것이다.
	virtual void OnFocus() = 0; //양쪽에다가 다 들어간다고 가정하겠다.

	virtual void OffFocus() = 0;
};
