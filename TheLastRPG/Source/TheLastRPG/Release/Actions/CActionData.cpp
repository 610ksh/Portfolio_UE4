#include "Release/Actions/CActionData.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	// Attachment (Weapon)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}

	// Equipment (Action)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->SetEquipData(EquipmentData);
		Equipment->SetUnequipData(UnequipmentData);
		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
		Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
	}
}