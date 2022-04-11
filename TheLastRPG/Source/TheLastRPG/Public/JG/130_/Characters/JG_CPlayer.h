// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG_CPlayer.generated.h"

//
UCLASS()
class THELASTRPG_API AJG_CPlayer : public ACharacter
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UJG_CMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UJG_COptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UJG_CStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UJG_CStateComponent* State;

public:
	// Sets default values for this character's properties
	AJG_CPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);


private:
	void OnRunning();
	void OffRunning();
	void OnAvoid();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType_JG InPrevType, EStateType_JG InNewType);

public:
	void Begin_Roll();
	void End_Roll();

	void Begin_Backstep();
	void End_Backstep();

//private:
//	class AJG_CSword* Sword;
//
//private:
//	void OnSword();
//	// 버그픽스용

private:
	void OnOneHand();

};
