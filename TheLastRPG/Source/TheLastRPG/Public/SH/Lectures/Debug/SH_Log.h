// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Log.generated.h"

/*
	Test�� ���� LogŬ������.
	CLog Ŭ������ �ִ� Log����� Ȱ����.
*/

UCLASS()
class THELASTRPG_API ASH_Log : public AActor
{
	GENERATED_BODY()
	
public:	
	ASH_Log();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float Time;
};
