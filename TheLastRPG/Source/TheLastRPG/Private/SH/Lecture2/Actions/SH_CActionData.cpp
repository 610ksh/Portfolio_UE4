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

	if (!!AttachmentClass) // Attachment 
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CAttachment>(AttachmentClass, transform, InOwnerCharacter); // ĳ���Ϳ� ������
		Attachment->SetActorLabel(GetLableName(InOwnerCharacter, "_Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform); // ���������� Ȯ��
	}

	if (!!EquipmentClass) // Equipment
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CEquipment>(EquipmentClass, transform, InOwnerCharacter); // ����
		Equipment->SetActorLabel(GetLableName(InOwnerCharacter, "_Equipment"));
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // ĳ���Ϳ� ����
		Equipment->SetData(EquipmentData); // ������ ���ε�
		Equipment->SetColor(EquipmentColor);

		UGameplayStatics::FinishSpawningActor(Equipment, transform); // ���������� Ȯ��
		if (!!Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ASH_CAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ASH_CAttachment::OnUnequip);
		}
	}

	if (!!DoActionClass) // DoAction
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CDoAction>(DoActionClass, transform, InOwnerCharacter); // ����
		DoAction->SetActorLabel(GetLableName(InOwnerCharacter, "_DoAction"));
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // ĳ���Ϳ� ����
		DoAction->SetDatas(DoActionDatas);

		UGameplayStatics::FinishSpawningActor(DoAction, transform); // ���������� Ȯ��

		if (!!Equipment)
		{
			DoAction->SetEquipped(Equipment->GetEquipped());
		}

		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ASH_CDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ASH_CDoAction::OnAttachmentEndOverlap);

			Attachment->OnAttachmentCollision.AddDynamic(DoAction, &ASH_CDoAction::OnAttachmentCollision);
			Attachment->OffAttachmentCollision.AddDynamic(DoAction, &ASH_CDoAction::OffAttachmentCollision);
		}
	}
}

FString USH_CActionData::GetLableName(class ACharacter* InOwnerCharacter, FString InName)
{
	FString str;
	//str.Append(InOwnerCharacter->GetActorLabel());
	str.Append(InOwnerCharacter->GetActorLabel().Replace(L"SH_BP_CAction", L""));
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	str.Append(GetName().Replace(L"DA_", L"")); // DA_�� ��������

	return str;
}