#include "SH/Lecture2/Notifies/SH_ActionCAnimNotifyState_Equip.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/SH_Global.h"

FString USH_ActionCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void USH_ActionCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetEquipment()->Begin_Equip();
}

void USH_ActionCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetEquipment()->End_Equip();
}