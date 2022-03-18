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
	CheckNull_SH(MeshComp); // 노티파이를 쓸때 MeshComp가 없을때가 있다. 체크해주자.

	// 메시의 오너가 캐릭터가 됨
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->Begin_Unequip();
}

void USH_CAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull_SH(MeshComp); // 노티파이를 쓸때 MeshComp가 없을때가 있다. 체크해주자.

	// 메시의 오너가 캐릭터가 됨
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull_SH(rifle);

	rifle->GetRifle()->End_Unequip();
}
