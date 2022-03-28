#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CStateComponent.generated.h"

UENUM(BlueprintType)
enum class SH_EStateType : uint8
{
	Idle, Roll, Backstep, Equip, Action, Hitted, Dead, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, SH_EStateType, InPrevType, SH_EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == SH_EStateType::Idle; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == SH_EStateType::Roll; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == SH_EStateType::Backstep; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == SH_EStateType::Equip; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == SH_EStateType::Action; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsHittedMode() { return Type == SH_EStateType::Hitted; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDeadMode() { return Type == SH_EStateType::Dead; }

public:
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();

private:
	void ChangeType(SH_EStateType InType);

public:	
	USH_CStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;
private:
	SH_EStateType Type;
};
