#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h" // for EActionType
#include "SH_CActionAnimInstance.generated.h"

UCLASS()
class THELASTRPG_API USH_CActionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EActionType ActionType;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);
};
