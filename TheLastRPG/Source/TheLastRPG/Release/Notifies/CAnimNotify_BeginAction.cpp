#include "Release/Notifies/CAnimNotify_BeginAction.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CAction.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Global.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentAction()->GetDoAction()->Begin_DoAction();
}