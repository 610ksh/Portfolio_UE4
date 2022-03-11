// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JG_CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType_JG : uint8
{
	Unarmed, OneHand, TwoHand, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged_JG, EActionType_JG, InPrevType, EActionType_JG, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API UJG_CActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UJG_CActionData* Datas[(int32)EActionType_JG::Max];

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE class UJG_CActionData* GetCurrent(){return Datas[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType_JG::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType_JG::OneHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType_JG::TwoHand; }

public:
	// Sets default values for this component's properties
	UJG_CActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetUnarmedMode();
	void SetOneHandMode();
	void SetTwoHandMode();

private:
	void SetMode(EActionType_JG InType);
	void ChangeType(EActionType_JG InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged_JG OnActionTypeChanged;

private:
	EActionType_JG Type;


};
