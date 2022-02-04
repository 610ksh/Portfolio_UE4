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
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UJG_UserWidget_CrossHair> CrossHairClass;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected:
	// ���� private������ OnZoomIn���� ī�޶� ������ �������� ���� protected��ȯ
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomOut();
public:
	FORCEINLINE class AJG_Rifle* GetRifle() override { return Rifle; }
	FORCEINLINE TSubclassOf<class UMatineeCameraShake> GetCameraShakeClass() { return CameraShakeClass; }

public:
	AJG_Player();

	void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnFocus() override;
	void OffFocus() override;

	void PlayCameraShake();

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

	void OnFire();
	void OffFire();

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
	class UJG_UserWidget_CrossHair* CrossHair;
};
