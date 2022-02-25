// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "JG_CAnimNotifyState_Equip.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API UJG_CAnimNotifyState_Equip : public UAnimNotifyState
{
	GENERATED_BODY()
	public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
