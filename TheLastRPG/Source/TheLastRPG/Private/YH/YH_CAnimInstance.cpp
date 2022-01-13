// Fill out your copyright notice in the Description page of Project Settings.

#include "YH/YH_CAnimInstance.h"
#include "YH/Global_YH.h"
#include "GameFramework/Character.h"

void UYH_CAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UYH_CAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);
	//���������ӿ�ũ�� �ִ�.
	Speed = OwnerCharacter->GetVelocity().Size2D();
	//���ͷ����̴�.
}
