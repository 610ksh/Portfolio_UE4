#include "Release/Notifies/CAnimNotifyState_Collision.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Global.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACAttachment* attachment = action->GetCurrentActionData()->GetAttachment();
	CheckNull(attachment);

	attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = Helpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACAttachment* attachment = action->GetCurrentActionData()->GetAttachment();
	CheckNull(attachment);

	attachment->OffCollision();
}