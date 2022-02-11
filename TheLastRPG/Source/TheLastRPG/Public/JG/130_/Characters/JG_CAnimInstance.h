// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JG_CAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class THELASTRPG_API UJG_CAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected: //블루프린트는 상속받아서 접근하기 때문에 private X
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Direction;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
