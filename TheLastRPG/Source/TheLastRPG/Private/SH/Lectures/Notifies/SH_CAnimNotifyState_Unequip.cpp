#include "SH/Lectures/Notifies/SH_CAnimNotifyState_Unequip.h"
#include "SH/Lectures/SH_IRifle.h"
#include "SH/Lectures/SH_CRifle.h"
#include "SH/SH_Global.h"


FString USH_CAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void USH_CAnimNotifyState_Unequip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull_SH(MeshComp); // ��Ƽ���̸� ���� MeshComp�� �������� �ִ�. üũ������.

	// �޽��� ���ʰ� ĳ���Ͱ� ��
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->Begin_Unequip();
}

void USH_CAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull_SH(MeshComp); // ��Ƽ���̸� ���� MeshComp�� �������� �ִ�. üũ������.

	// �޽��� ���ʰ� ĳ���Ͱ� ��
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->End_Unequip();
}
