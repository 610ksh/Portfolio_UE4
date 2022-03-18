// Fill out your copyright notice in the Description page of Project Settings.

#include "YH/YH_CAnimInstance.h"
#include "YH/Global_YH.h"
#include "YH/Weapon/YH_IRifle.h"
#include "YH/Weapon/YH_CRifle.h"
#include "GameFramework/Character.h"

void UYH_CAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UYH_CAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	YH_CheckNull(OwnerCharacter);
	//���������ӿ�ũ�� �ִ�.
	Speed = OwnerCharacter->GetVelocity().Size2D();
	//���ͷ����̴�.
	//pitch�������� ������������ C �ڵ�
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	if (!!rifle)
	{
		//���� ó���� rifle ������ �ߴ°��� CRifle.h �߰� ���ؼ�
		bEquipped = rifle->GetRifle()->GetEquipped();
		bAiming = rifle->GetRifle()->GetAiming();//�� ���̹� �����ð� �����ٰ� �ִ��ν��Ͻ����ٰ� ����
	}
}
