// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Notifies/JG_CAnimNotify_EndRoll.h"
#include "JG/130_/Characters/JG_CPlayer.h"
#include "JG/JG_Global.h"


FString UJG_CAnimNotify_EndRoll::GetNotifyName_Implementation() const
{
	return "Roll";
}

void UJG_CAnimNotify_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner()); 

	AJG_CPlayer* player = Cast< AJG_CPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Roll();
}
