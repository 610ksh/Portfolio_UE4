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
	//게임프레임워크에 있다.
	Speed = OwnerCharacter->GetVelocity().Size2D();
	//벡터랭쓰이다.
	//pitch블프에서 가져오기위한 C 코드
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	if (!!rifle)
	{
		//여기 처음에 rifle 빨간줄 뜨는것은 CRifle.h 추가 안해서
		bEquipped = rifle->GetRifle()->GetEquipped();
		bAiming = rifle->GetRifle()->GetAiming();//겟 에이밍 라이플거 가져다가 애님인스턴스에다가 세팅
	}
}
