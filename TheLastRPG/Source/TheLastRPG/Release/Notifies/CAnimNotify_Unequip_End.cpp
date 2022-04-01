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
	CLog::Print(action->GetName());
	CLog::Print(action->GetCurrentActionData()->GetName()); // 여기서 읽지 못함. 
	/// 결론 : GEtCurrentActionData를 못가져옴
	CLog::Print(action->GetCurrentActionData()->GetEquipment()->GetName());
	action->GetCurrentActionData()->GetEquipment()->End_Unequip();
}