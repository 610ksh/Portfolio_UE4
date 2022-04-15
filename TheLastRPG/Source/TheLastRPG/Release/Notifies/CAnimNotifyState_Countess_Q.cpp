#include "Release/Notifies/CAnimNotifyState_Countess_Q.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Global.h"

FString UCAnimNotifyState_Countess_Q::GetNotifyName_Implementation() const
{
	return "Skill_Q";
}

void UCAnimNotifyState_Countess_Q::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentAction()->GetDoAction()->Begin_Skill_Q();
}

void UCAnimNotifyState_Countess_Q::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrentAction()->GetDoAction()->End_Skill_Q();
}