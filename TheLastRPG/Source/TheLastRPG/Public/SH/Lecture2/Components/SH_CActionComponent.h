#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, OneHand, TwoHand, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class USH_CActionData* Datas[(int32)EActionType::Max]; // Player BP 에디터에서 넣어줄 ActionData를 받는 배열

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class USH_CActionData* GetCurrent() { return Datas[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

public:	
	USH_CActionComponent();

	void SetUnarmedMode();
	void SetOneHandMode();
	void SetTwoHandMode();

public:
	void DoAction();

protected:
	virtual void BeginPlay() override;

private:
	void SetMode(EActionType InType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	EActionType Type;

};
