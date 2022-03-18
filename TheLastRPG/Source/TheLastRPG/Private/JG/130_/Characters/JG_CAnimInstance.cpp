// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Characters/JG_CAnimInstance.h"
#include "JG/JG_Global.h"
#include "GameFrameWork/Character.h"

void UJG_CAnimInstance::NativeBeginPlay()
{
	//
	Super::NativeBeginPlay();
}

void UJG_CAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	JG_CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());

}
