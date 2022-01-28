// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JG/JG_IRifle.h"
#include "GameFramework/Character.h"
#include "JG_Player.generated.h"

UCLASS()
class THELASTRPG_API AJG_Player : public ACharacter, public IJG_IRifle
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* Camera;

public:
	FORCEINLINE class AJG_Rifle* GetRifle() override { return Rifle; }

public:	
	AJG_Player();

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
	void OnRunning();
	void OffRunning();

	void OnRifle();

	void OnAim();
	void OffAim();

public:
	// C������ �̷��� �̺�Ʈ ���Ǹ� ���ְ�, �̺�Ʈ ������ BP�� C�� �ڽĿ���
	// �ʿ��Ѵ�� �����ؼ� ���
	UFUNCTION(BlueprintCallable) 
	void ChangeColor(FLinearColor InColor);

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AJG_Rifle* Rifle;
};
