#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH_CActionPlayer.generated.h"

UCLASS()
class THELASTRPG_API ASH_CActionPlayer : public ACharacter
{
	GENERATED_BODY()

private: // Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CActionComponent* Action;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_COptionActorComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStateComponent* State;

public:
	ASH_CActionPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

private:
	void OnAvoid();

private:
	UFUNCTION() // for Delegate about StateComponent
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Begin_Roll();
	void Begin_Backstep();
	
public:
	void End_Roll();
	void End_Backstep();

private:
	void OnOneHand();
	void OnDoAction();
};
