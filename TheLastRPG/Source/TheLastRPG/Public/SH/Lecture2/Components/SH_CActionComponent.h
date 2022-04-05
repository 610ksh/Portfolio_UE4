#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CActionComponent.generated.h"

UENUM(BlueprintType)
enum class ESH_ActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, FireStorm, IceBall, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSH_ActionTypeChanged, ESH_ActionType, InPrevType, ESH_ActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class USH_CActionData* DataAssets[(int32)ESH_ActionType::Max]; // Player BP 에디터에서 넣어줄 ActionData를 받는 배열

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class USH_CAction* GetCurrent() { return Datas[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == ESH_ActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == ESH_ActionType::Fist; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == ESH_ActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == ESH_ActionType::TwoHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == ESH_ActionType::Warp; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFireStormMode() { return Type == ESH_ActionType::FireStorm; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIceBallMode() { return Type == ESH_ActionType::IceBall; }

public:	
	USH_CActionComponent();
	
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();
	UFUNCTION(BlueprintCallable)
		void SetTwoHandMode();
	UFUNCTION(BlueprintCallable)
		void SetWarpMode();
	UFUNCTION(BlueprintCallable)
		void SetIceBallMode();

	void SetFistMode();
	void SetOneHandMode();
	void SetFireStormMode();
	
	void OffAllCollision();
	void DestroyAllActions();

public:
	void DoAction();

	void DoAim();
	void UndoAim();

private:
	void SetAimMode(bool InAim);

protected:
	virtual void BeginPlay() override;

private:
	void SetMode(ESH_ActionType InType);
	void ChangeType(ESH_ActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FSH_ActionTypeChanged OnActionTypeChanged;

private:
	ESH_ActionType Type;
	class USH_CAction* Datas[(int32)ESH_ActionType::Max];
};
