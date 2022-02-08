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
	//최초로 애니메이션 비긴플레이
	virtual void NativeBeginPlay() override;
	//최초로 업데이트
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//blueprintUpdateAnimation은 버추얼함수가 아니라서 재정의 할수없다. 그래서 이걸사용
private:
	class ACharacter* OwnerCharacter;
};
