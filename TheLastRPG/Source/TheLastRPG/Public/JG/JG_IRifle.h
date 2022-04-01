// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JG_IRifle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJG_IRifle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELASTRPG_API IJG_IRifle
{
	GENERATED_BODY()

	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// 인터페이스. 라이플을 드는 캐릭터들은 여러개. 이 여러개의 캐릭터들이 사용하는 라이플의 이름명(함수명)을 똑같이 하기 위해 사용. 정의는 부모 클래스의 모든 멤버를 하위 클래스가 물려 받는 것. 유연성 증가.
	// -> 애자일과 연결. 애자일 프로세스는 완전한 요구사항이 도출되지 않은상태에서 빠르게 개발하면서 지속적으로 새로운 요구사항과 변경사항을 적용하는 방식
	virtual class AJG_Rifle* GetRifle() = 0; // = 0 은 순수 가상 함수(얘를 상속한애는 무조건 재정의)
	virtual void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) = 0;
	virtual void OnFocus() = 0;
	virtual void OffFocus() = 0;
};
