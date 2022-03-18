// Fill out your copyright notice in the Description page of Project Settings.


#include "YH/ActionRPG/YH_CActionAnimInstance.h"
#include "YH/Global_YH.h"
#include "GameFramework/Character.h"

void UYH_CActionAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	YH_CheckNull(character);
}

void UYH_CActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	YH_CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
}
