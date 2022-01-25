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
	// EditAnywhere�� ���Ϳ� �ٴ°� �ƴ϶��, �����Ϳ��� ���̷��� �ؾ���
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP���� �б� ����
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation") // BP���� �б� ����
		bool bEquipped;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	class ACharacter* OwnerCharacter;
};
