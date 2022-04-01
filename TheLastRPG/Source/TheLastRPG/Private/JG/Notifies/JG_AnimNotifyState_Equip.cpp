// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Notifies/JG_AnimNotifyState_Equip.h"
#include "JG/JG_Global.h"
#include "JG/JG_IRifle.h"
#include "JG/JG_Rifle.h"

FString UJG_AnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UJG_AnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	JG_CheckNull(MeshComp);

	IJG_IRifle* rifle = Cast<IJG_IRifle>(MeshComp->GetOwner());
	JG_CheckNull(rifle);

	rifle->GetRifle()->Begin_Equip();
}

void UJG_AnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	JG_CheckNull(MeshComp);

	IJG_IRifle* rifle = Cast<IJG_IRifle>(MeshComp->GetOwner());
	JG_CheckNull(rifle);

	rifle->GetRifle()->End_Equip();
}
