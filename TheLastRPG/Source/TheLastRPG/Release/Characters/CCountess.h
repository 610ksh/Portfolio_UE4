#pragma once

#include "Release/Components/CStateComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCountess.generated.h"

UCLASS()
class THELASTRPG_API ACCountess : public ACharacter
{
	GENERATED_BODY()

private: // Scene component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor component
	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montages;

public:
	ACCountess();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	void OnAvoid();

private:
	UFUNCTION()
		void OnStateTypeChanged(ECountessStateType InPrevType, ECountessStateType InNewType);

private:
	void Begin_Roll();
	void End_Roll();

	void Begin_Backstep();
	void End_Backstep();
};
