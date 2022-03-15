// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Log.generated.h"

/*
	Test를 위한 Log클래스임.
	CLog 클래스에 있는 Log기능을 활용함.
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
