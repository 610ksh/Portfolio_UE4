#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, FireStorm, Throw, Max,
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Q, E, R, F, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS(ClassGroup = (GameProject), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* DataAssets[(int32)EActionType::Max];

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCAction* GetCurrentAction() { return Datas[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == EActionType::Warp; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFireStormMode() { return Type == EActionType::FireStorm; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsThrowMode() { return Type == EActionType::Throw; }

public:
	UCActionComponent();

	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();
	UFUNCTION(BlueprintCallable)
		void SetOneHandMode();
	UFUNCTION(BlueprintCallable)
		void SetTwoHandMode();

	void SetFistMode();
	void SetWarpMode();
	void SetFireStormMode();
	void SetThrowMode();

public: // Attack
	void DoAction();
	void DoSkillAction(ESkillType InType);

	void DoAim();
	void UndoAim();

protected:
	virtual void BeginPlay() override;

private:
	void SetUnarmedMode_Begin();
	void SetMode(EActionType InType);
	void SetAimMode(bool InAim);
	void ChangeType(EActionType InNewType);

public:
	FActionTypeChanged OnActionTypeChanged;

private:
	UPROPERTY(VisibleAnywhere)
		EActionType Type;

	class UCAction* Datas[(int32)EActionType::Max];
};
