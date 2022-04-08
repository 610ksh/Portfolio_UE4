// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Actions/JG_CActionData.h"
#include "JG/130_/Actions/JG_CAttachment.h"
#include "JG/130_/Actions/JG_CEquipment.h"
#include "JG/JG_Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


//
void UJG_CActionData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;

	// Attachment 
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<AJG_CAttachment>(AttachmentClass, transform, InOwnerCharacter); 
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");
		UGameplayStatics::FinishSpawningActor(Equipment, transform); 
	}
	 
	// Equipment
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<AJG_CEquipment>(EquipmentClass, transform, InOwnerCharacter); 
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); 
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->SetData(EquipmentData); 
		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &AJG_CAttachment::OnEquip);
		Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &AJG_CAttachment::OnUnequip);
	}
}