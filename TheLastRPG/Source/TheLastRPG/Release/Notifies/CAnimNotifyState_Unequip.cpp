#include "Release/Notifies/CAnimNotifyState_Unequip.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

FString UCAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip_State";
}

void UCAnimNotifyState_Unequip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentActionData()->GetEquipment()->Begin_Unequip();
}

void UCAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentActionData()->GetEquipment()->End_Unequip();
	action->SetUnarmedMode();
}