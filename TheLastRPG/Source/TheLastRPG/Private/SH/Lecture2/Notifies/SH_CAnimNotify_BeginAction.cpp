#include "SH/Lecture2/Notifies/SH_CAnimNotify_BeginAction.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void USH_CAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull_SH(MeshComp); // 메시 유무
	CheckNull_SH(MeshComp->GetOwner()); // 캐릭터 유무(Actor)

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull_SH(action);

	action->GetCurrent()->GetDoAction()->Begin_DoAction();
}
