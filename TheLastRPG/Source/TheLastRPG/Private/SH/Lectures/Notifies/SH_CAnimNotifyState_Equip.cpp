#include "SH/Lectures/Notifies/SH_CAnimNotifyState_Equip.h"
#include "SH/Lectures/SH_IRifle.h"
#include "SH/Lectures/SH_CRifle.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void USH_CAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull_SH(MeshComp); // ��Ƽ���̸� ���� MeshComp�� �������� �ִ�. üũ������.

	// �޽��� ���ʰ� ĳ���Ͱ� ��
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->Begin_Equip();
}

void USH_CAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull_SH(MeshComp); // ��Ƽ���̸� ���� MeshComp�� �������� �ִ�. üũ������.

	// �޽��� ���ʰ� ĳ���Ͱ� ��
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->End_Equip();

}
