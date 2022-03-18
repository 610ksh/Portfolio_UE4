#include "SH/Lectures/SH_CAnimInstance.h"
#include "SH/Lectures/SH_IRifle.h"
#include "SH/Lectures/SH_CRifle.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

void USH_CAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void USH_CAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull_SH(OwnerCharacter); // NULL이면 return함

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter);
	if (!!rifle) // ISH_IRifle를 상속한 총이 있으면
	{
		bEquipped = rifle->GetRifle()->GetEquipped();
		bAiming = rifle->GetRifle()->GetAiming();
	}
}