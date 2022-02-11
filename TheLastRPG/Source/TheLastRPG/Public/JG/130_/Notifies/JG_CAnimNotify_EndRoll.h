// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "JG_CAnimNotify_EndRoll.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API UJG_CAnimNotify_EndRoll : public UAnimNotify
{
	GENERATED_BODY()
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
