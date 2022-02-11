// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SH_CAnimInstance.generated.h"

UCLASS()
class THELASTRPG_API USH_CAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

protected:
	// EditAnywhere는 액터에 붙는거 아니라면, 에디터에서 보이려면 해야함
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP에서 읽기 전용
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP에서 읽기 전용
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP에서 읽기 전용
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP에서 읽기 전용
		bool bEquipped;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP에서 읽기 전용
		bool bAiming;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	class ACharacter* OwnerCharacter;
};
