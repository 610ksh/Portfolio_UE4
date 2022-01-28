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
	//���� �����Լ��� ������ �� �������̽��� �߻�Ŭ������ ��ӹ����ֵ��� �ݵ�� ���������Լ��� ������ ������ ������ ���� ��ӹ޴¾ֵ� �߻�Ŭ������ �Ǽ� ��üȭ �ɼ� ����.
	virtual class AYH_CRifle* GetRifle() = 0;
};
