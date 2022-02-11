// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/JG_AnimInstance.h"
#include "JG/JG_Global.h"
#include "JG/JG_IRifle.h"
#include "JG/JG_Rifle.h"
#include "GameFramework/Character.h"

void UJG_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UJG_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter); 

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IJG_IRifle* rifle = Cast<IJG_IRifle>(OwnerCharacter);
	if (!!rifle)
	{
		bEquipped = rifle->GetRifle()->GetEquipped();
		bAiming = rifle->GetRifle()->GetAiming();
	}
}