#include "Release/Actions/CActionData.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Actions/CAction.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCAction** OutAction)
{
	FTransform transform;

	// Attachment (Weapon)
	ACAttachment* attachment[2] = {}; // 최대 2개 (양손검)
	for (int32 i = 0; i < AttachmentClass.Num(); ++i)
	{
		if (!!AttachmentClass[i])
		{
			attachment[i] = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass[i], transform, InOwnerCharacter);
			attachment[i]->SetActorLabel(GetLableName(InOwnerCharacter, "Attachment", AttachmentClass[i]->GetName()));
			UGameplayStatics::FinishSpawningActor(attachment[i], transform);
		}
	}

	// Equipment (Equip, Unequip)
	ACEquipment* equipment = NULL;
	if (!!EquipmentClass)
	{
		equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		equipment->SetActorLabel(GetLableName(InOwnerCharacter, "Equipment"));
		equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		if (!!EquipmentData.AnimMontage)
			equipment->SetEquipData(EquipmentData);
		if (!!UnequipmentData.AnimMontage)
			equipment->SetUnequipData(UnequipmentData);
		equipment->SetColor(EquipmentColor);
		UGameplayStatics::FinishSpawningActor(equipment, transform);

		for (int32 i = 0; i < AttachmentClass.Num(); i++)
		{
			if (!!attachment[i])
			{
				equipment->OnEquipmentDelegate.AddDynamic(attachment[i], &ACAttachment::OnEquip);
				equipment->OnUnequipmentDelegate.AddDynamic(attachment[i], &ACAttachment::OnUnequip);
			}
		}
	}

	// DoAction (Attack)
	ACDoAction* doAction = NULL;
	if (!!DoActionClass)
	{
		doAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		doAction->SetActorLabel(GetLableName(InOwnerCharacter, "DoAction"));
		doAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		doAction->SetAttackDatas(AttackDatas);
		doAction->SetSkillDatas(SkillDatas);
		UGameplayStatics::FinishSpawningActor(doAction, transform);

		if (!!equipment)
		{
			doAction->SetEquipped(equipment->GetEquipped());
		}

		for (int32 i = 0; i < AttachmentClass.Num(); ++i)
		{
			if (!!attachment[i])
			{
				attachment[i]->OnAttachmentBeginOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentBeginOverlap);
				attachment[i]->OnAttachmentEndOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentEndOverlap);

				attachment[i]->OnAttachmentCollision.AddDynamic(doAction, &ACDoAction::OnAttachmentCollision);
				attachment[i]->OffAttachmentCollision.AddDynamic(doAction, &ACDoAction::OffAttachmentCollision);
			}
		}
	} // DoAction

	*OutAction = NewObject<UCAction>(); // 런타임중 동적할당
	for (int32 i = 0; i < AttachmentClass.Num(); ++i)
		(*OutAction)->Attachment[i] = attachment[i];
	(*OutAction)->Equipment = equipment;
	(*OutAction)->DoAction = doAction;
	(*OutAction)->EquipmentColor = EquipmentColor;
	(*OutAction)->AttachCount = AttachmentClass.Num();
}

FString UCActionData::GetLableName(class ACharacter* InOwnerCharacter, const FString& InName, const FString& InAttachmentClassName)
{
	FString str;
	str.Append(InOwnerCharacter->GetActorLabel());
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	if (InName == "Attachment")
		str.Append(GetAttachmentName(InAttachmentClassName));
	else
		str.Append(GetName().Replace(L"DA_Countess_", L""));
	return str;
}

FString UCActionData::GetAttachmentName(const FString& name)
{
	int32 underbarCount = 0;
	FString ret = "";
	ret.Reserve(10);

	for (int32 i = 0; i < name.Len() - 2; ++i)
	{
		if (name[i] == '_' && underbarCount < 2)
		{
			underbarCount++;
			continue;
		}

		if (underbarCount == 2)
			ret.AppendChar(name[i]);
	}

	return ret;
}