#include "Release/Notifies/CAnimNotify_Unequip_End.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

FString UCAnimNotify_Unequip_End::GetNotifyName_Implementation() const
{
	return "Unequip_End";
}

void UCAnimNotify_Unequip_End::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentActionData()->GetEquipment()->End_Unequip();
	action->SetUnarmedMode();
}