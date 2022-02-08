// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YH_CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API UYH_CAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bEquipped;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bAiming;
public:
	//���ʷ� �ִϸ��̼� ����÷���
	virtual void NativeBeginPlay() override;
	//���ʷ� ������Ʈ
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//blueprintUpdateAnimation�� ���߾��Լ��� �ƴ϶� ������ �Ҽ�����. �׷��� �̰ɻ��
private:
	class ACharacter* OwnerCharacter;
};
