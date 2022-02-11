// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JG_CPlayer.generated.h"

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
	class UJG_COptionComponent* Option;

	
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
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
};
