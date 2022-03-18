#include "SH/Lecture2/Notifies/SH_CAnimNotifyState_Collision.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void USH_CAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull_SH(MeshComp);
	CheckNull_SH(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull_SH(action);

	ASH_CAttachment* attachment = action->GetCurrent()->GetAttachment();
	CheckNull_SH(attachment);

	attachment->OnCollision();
}

void USH_CAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull_SH(MeshComp);
	CheckNull_SH(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull_SH(action);

	ASH_CAttachment* attachment = action->GetCurrent()->GetAttachment();
	CheckNull_SH(attachment);

	attachment->OffCollision();
}