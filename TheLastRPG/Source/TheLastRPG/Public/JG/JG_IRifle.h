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

	// �������̽�. �������� ��� ĳ���͵��� ������. �� �������� ĳ���͵��� ����ϴ� �������� �̸���(�Լ���)�� �Ȱ��� �ϱ� ���� ���. ���Ǵ� �θ� Ŭ������ ��� ����� ���� Ŭ������ ���� �޴� ��. ������ ����.
	// -> �����ϰ� ����. ������ ���μ����� ������ �䱸������ ������� �������¿��� ������ �����ϸ鼭 ���������� ���ο� �䱸���װ� ��������� �����ϴ� ���
	virtual class AJG_Rifle* GetRifle() = 0; // = 0 �� ���� ���� �Լ�(�긦 ����Ѿִ� ������ ������)
	virtual void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) = 0;
	virtual void OnFocus() = 0;
	virtual void OffFocus() = 0;
};
