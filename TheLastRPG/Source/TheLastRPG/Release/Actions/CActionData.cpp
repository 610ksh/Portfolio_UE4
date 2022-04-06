#include "Release/Actions/CActionData.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	// Attachment (Weapon)
	for (int32 i = 0; i < AttachmentClass.Num(); ++i)
	{
		if (!!AttachmentClass[i])
		{
			Attachment.Add(InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass[i], transform, InOwnerCharacter));
			Attachment[i]->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment_" + FString::FromInt(i));
			UGameplayStatics::FinishSpawningActor(Attachment[i], transform);
		}
	}

	// Equipment (Action)
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetEquipData(EquipmentData);
		Equipment->SetUnequipData(UnequipmentData);
		Equipment->SetColor(EquipmentColor);
		UGameplayStatics::FinishSpawningActor(Equipment, transform);


		for (int32 i = 0; i < AttachmentClass.Num(); i++)
		{
			if (!!Attachment[i])
			{
				Equipment->OnEquipmentDelegate.AddDynamic(Attachment[i], &ACAttachment::OnEquip);
				Equipment->OnUnequipmentDelegate.AddDynamic(Attachment[i], &ACAttachment::OnUnequip);
			}
		}
	}

	// DoAction
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_DoAction");
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetDatas(DoActionDatas);
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		for (int32 i = 0; i < AttachmentClass.Num(); ++i)
		{
			if (!!Attachment[i])
			{
				Attachment[i]->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
				Attachment[i]->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);

				Attachment[i]->OnAttachmentCollision.AddDynamic(DoAction, &ACDoAction::OnAttachmentCollision);
				Attachment[i]->OffAttachmentCollision.AddDynamic(DoAction, &ACDoAction::OffAttachmentCollision);
			}
		}
	}
}

ACAttachment* UCActionData::GetAttachment(const int& idx)
{
	if (Attachment.IsValidIndex(idx))
		return Attachment[idx];
	return NULL;
}
