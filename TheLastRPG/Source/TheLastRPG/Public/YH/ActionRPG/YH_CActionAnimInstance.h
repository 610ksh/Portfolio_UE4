// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YH_CActionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API UYH_CActionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
