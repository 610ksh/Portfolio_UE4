#include "SH/Lecture2/Actions/SH_CActionData.h"

#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void USH_CActionData::BeginPlay(class ACharacter* InOwnerCharacter, class USH_CAction** OutAction)
{
	FTransform transform;

	ASH_CAttachment* attachment = NULL;
	if (!!AttachmentClass) // Attachment 
	{
		attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CAttachment>(AttachmentClass, transform, InOwnerCharacter); // 캐릭터에 부착됨
		attachment->SetActorLabel(GetLableName(InOwnerCharacter, "_Attachment"));
		UGameplayStatics::FinishSpawningActor(attachment, transform); // 최종적으로 확정
	}

	ASH_CEquipment* equipment = NULL;
	if (!!EquipmentClass) // Equipment
	{
		equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CEquipment>(EquipmentClass, transform, InOwnerCharacter); // 생성
		equipment->SetActorLabel(GetLableName(InOwnerCharacter, "_Equipment"));
		equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // 캐릭터에 장착
		equipment->SetData(EquipmentData); // 데이터 업로드
		equipment->SetColor(EquipmentColor);

		UGameplayStatics::FinishSpawningActor(equipment, transform); // 최종적으로 확정
		if (!!attachment)
		{
			equipment->OnEquipmentDelegate.AddDynamic(attachment, &ASH_CAttachment::OnEquip);
			equipment->OnUnequipmentDelegate.AddDynamic(attachment, &ASH_CAttachment::OnUnequip);
		}
	}

	ASH_CDoAction* doAction = NULL;
	if (!!DoActionClass) // DoAction
	{
		doAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CDoAction>(DoActionClass, transform, InOwnerCharacter); // 생성
		doAction->SetActorLabel(GetLableName(InOwnerCharacter, "_DoAction"));
		doAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // 캐릭터에 장착
		doAction->SetDatas(DoActionDatas);

		UGameplayStatics::FinishSpawningActor(doAction, transform); // 최종적으로 확정

		if (!!equipment)
		{
			doAction->SetEquipped(equipment->GetEquipped());
		}

		if (!!attachment)
		{
			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &ASH_CDoAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &ASH_CDoAction::OnAttachmentEndOverlap);
			
			attachment->OnAttachmentCollision.AddDynamic(doAction, &ASH_CDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &ASH_CDoAction::OffAttachmentCollision);
		}
	}

	*OutAction = NewObject<USH_CAction>();
	(*OutAction)->Attachment = attachment;
	(*OutAction)->Equipment = equipment;
	(*OutAction)->DoAction = doAction;
	(*OutAction)->EquipmentColor = EquipmentColor;
}

FString USH_CActionData::GetLableName(class ACharacter* InOwnerCharacter, FString InName)
{
	FString str;
	//str.Append(InOwnerCharacter->GetActorLabel());
	str.Append(InOwnerCharacter->GetActorLabel().Replace(L"SH_BP_CAction", L""));
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	str.Append(GetName().Replace(L"DA_", L"")); // DA_를 공백으로

	return str;
}