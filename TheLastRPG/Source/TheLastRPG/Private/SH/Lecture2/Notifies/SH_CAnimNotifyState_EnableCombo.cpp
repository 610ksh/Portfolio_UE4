#include "SH/Lecture2/Notifies/SH_CAnimNotifyState_EnableCombo.h"
#include "SH/Lecture2/Actions/SH_CDoAction_Melee.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return "EnableCombo";
}

void USH_CAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);
	
	ASH_CDoAction_Melee* melee = Cast<ASH_CDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->EnableCombo(); // ���ĺ��� �޺� �Է� ������
}

void USH_CAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ASH_CDoAction_Melee* melee = Cast<ASH_CDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->DisableCombo(); // ���ĺ��� �޺� �Է� �Ұ���
}