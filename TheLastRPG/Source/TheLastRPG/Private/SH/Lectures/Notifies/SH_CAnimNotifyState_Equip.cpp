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
	CheckNull(MeshComp); // 노티파이를 쓸때 MeshComp가 없을때가 있다. 체크해주자.

	// 메시의 오너가 캐릭터가 됨
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->Begin_Equip();
}

void USH_CAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp); // 노티파이를 쓸때 MeshComp가 없을때가 있다. 체크해주자.

	// 메시의 오너가 캐릭터가 됨
	ISH_IRifle* rifle = Cast<ISH_IRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->End_Equip();

}
