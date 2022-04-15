#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class ESH_BehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Avoid,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSH_BehaviorTypeChanged, ESH_BehaviorType, InPrevType, ESH_BehaviorType, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API USH_CBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";
	UPROPERTY(EditAnywhere)
		FName WarpKey = "Warp";

public:
	UFUNCTION(BlueprintPure)
		bool IsWaitMode();
	UFUNCTION(BlueprintPure)
		bool IsApproachMode();
	UFUNCTION(BlueprintPure)
		bool IsActionMode();
	UFUNCTION(BlueprintPure)
		bool IsPatrolMode();
	UFUNCTION(BlueprintPure)
		bool IsHittedMode();
	UFUNCTION(BlueprintPure)
		bool IsAvoidMode();

	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	USH_CBehaviorComponent();

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();

	class ASH_CActionPlayer* GetTargetPlayer(); // Character·Î ÇØµµ µÊ
	FVector GetWarpLocation();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(ESH_BehaviorType InType);
	ESH_BehaviorType GetType();

public:
	UPROPERTY(BlueprintAssignable)
		FSH_BehaviorTypeChanged OnBehaviorTypeChanged;

private:
	class UBlackboardComponent* Blackboard;
};
