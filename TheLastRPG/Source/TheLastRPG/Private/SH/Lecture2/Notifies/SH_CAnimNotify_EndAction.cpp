#include "SH/Lecture2/Notifies/SH_CAnimNotify_EndAction.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void USH_CAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp); // 메시 유무
	CheckNull(MeshComp->GetOwner()); // 캐릭터 유무(Actor)

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetDoAction()->End_DoActin();
}
