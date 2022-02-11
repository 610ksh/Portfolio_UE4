#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void USH_CActionData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;

	// Attachment
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CAttachment>(AttachmentClass, transform, InOwnerCharacter); // 생성
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");
		UGameplayStatics::FinishSpawningActor(Attachment, transform); // 최종적으로 확정
	}

	// Equipment
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CEquipment>(EquipmentClass, transform, InOwnerCharacter); // 생성
		Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // 캐릭터에 장착
		Equipment->SetData(EquipmentData); // 데이터 업로드

		UGameplayStatics::FinishSpawningActor(Equipment, transform); // 최종적으로 확정

		Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ASH_CAttachment::OnEquip);
		Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ASH_CAttachment::OnUnequip);
	}

	// DoAction
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CDoAction>(DoActionClass, transform, InOwnerCharacter); // 생성
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // 캐릭터에 장착
		DoAction->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_DoAction");
		DoAction->SetDatas(DoActionDatas);

		UGameplayStatics::FinishSpawningActor(DoAction, transform); // 최종적으로 확정
	}
}