// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Notifies/JG_CAnimNotifyState_Equip.h"
#include "JG/130_/Components/JG_CActionComponent.h"
#include "JG/130_/Actions/JG_CEquipment.h"
#include "JG/JG_Global.h"

FString UJG_CAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UJG_CAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJG_CActionComponent* action = JG_Helpers::GetComponent<UJG_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetEquipment()->Begin_Equip();
}

void UJG_CAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJG_CActionComponent* action = JG_Helpers::GetComponent<UJG_CActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetEquipment()->End_Equip();
}
