// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JG_CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType_JG : uint8
{
	Idle, Roll, Backstep, Equip, Action, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged_JG, EStateType_JG, InPrevType, EStateType_JG, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API UJG_CStateComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType_JG::Idle; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType_JG::Roll; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == EStateType_JG::Backstep; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType_JG::Equip; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == EStateType_JG::Action; }

public:
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();
	void SetEquipMode();
	void SetActionMode();

private:
	void ChangeType(EStateType_JG InType);


public:
	// Sets default values for this component's properties
	UJG_CStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged_JG OnStateTypeChanged;
private:
	EStateType_JG Type;
};
