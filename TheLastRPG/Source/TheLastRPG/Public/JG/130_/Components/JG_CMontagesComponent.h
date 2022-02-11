// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG_CMontagesComponent.generated.h"


USTRUCT(BlueprintType)
struct FMontageData_JG : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType_JG Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		bool bCanMove;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API UJG_CMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;
public:
	// Sets default values for this component's properties
	UJG_CMontagesComponent();

	void PlayRoll();
	void PlayBackstep();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void PlayAnimMontage(EStateType_JG InState);

private:
	FMontageData_JG* Datas[(int32)EStateType_JG::Max];
};
