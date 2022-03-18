#include "SH/Lecture2/Notifies/SH_CAnimNotifyState_Dead.h"
#include "SH/Lecture2/SH_ICharacter.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotifyState_Dead::GetNotifyName_Implementation() const
{
	return "Dead";
}

void USH_CAnimNotifyState_Dead::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull_SH(MeshComp);
	CheckNull_SH(MeshComp->GetOwner());

	ISH_ICharacter* character = Cast<ISH_ICharacter>(MeshComp->GetOwner());
	CheckNull_SH(character);

	character->Begin_Dead();
}

void USH_CAnimNotifyState_Dead::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull_SH(MeshComp);
	CheckNull_SH(MeshComp->GetOwner());

	ISH_ICharacter* character = Cast<ISH_ICharacter>(MeshComp->GetOwner());
	CheckNull_SH(character);

	character->End_Dead();
}