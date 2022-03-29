#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class ECountessActionType : uint8
{
	Unarmed, OneHand, TwoHand,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCountessActionTypeChanged, ECountessActionType, InPrevType, ECountessActionType, InNewType);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == ECountessActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == ECountessActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == ECountessActionType::TwoHand; }
public:	
	UCActionComponent();

	void SetUnarmedMode();
	void SetOneHandMode();
	void SetTwoHandMode();

protected:
	virtual void BeginPlay() override;

private:
	void SetMode(ECountessActionType InType);
	void ChangeType(ECountessActionType InNewType);

private:
	FCountessActionTypeChanged OnCountessActionTypeChanged;

private:
	ECountessActionType Type;
};
