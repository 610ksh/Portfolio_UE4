#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JG_AnimInstance.generated.h"


UCLASS()
class THELASTRPG_API UJG_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected: //��������Ʈ�� ��ӹ޾Ƽ� �����ϱ� ������ private X
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Speed;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	class ACharacter* OwnerCharacter;
};