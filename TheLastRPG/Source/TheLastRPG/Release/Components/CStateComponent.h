#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class ECountessStateType : uint8
{
	Idle, Roll, Backstep, Max,
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

public: // setter
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();

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
	UPROPERTY(VisibleDefaultsOnly)
		ECountessStateType Type;
};
