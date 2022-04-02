#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType) // 각 캐릭터마다 만들어주면 됨
enum class ECountessStateType : uint8
{
	Idle, Roll, Backstep, Equip, Unequip, Action, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCountessStateTypeChanged, ECountessStateType, InPrevType, ECountessStateType, InNewType);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public: // getter
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == ECountessStateType::Idle; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == ECountessStateType::Roll; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == ECountessStateType::Backstep; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == ECountessStateType::Equip; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnequipMode() { return Type == ECountessStateType::Unequip; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == ECountessStateType::Action; }

public: // setter
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();
	void SetEquipMode();
	void SetUnequipMode();
	void SetActionMode();

private:
	void ChangeType(ECountessStateType InType);

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FCountessStateTypeChanged OnCountessStateTypeChanged;

private:
	UPROPERTY(VisibleAnywhere)
		ECountessStateType Type;
};
