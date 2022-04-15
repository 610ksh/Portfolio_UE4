#include "Release/Notifies/CAnimNotify_EndAction.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CAction.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Global.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentAction()->GetDoAction()->End_DoAction();
}