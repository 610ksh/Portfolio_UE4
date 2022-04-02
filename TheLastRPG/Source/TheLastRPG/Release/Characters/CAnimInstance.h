#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Release/Components/CActionComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class THELASTRPG_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		ECountessActionType ActionType;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(ECountessActionType InPrevType, ECountessActionType InNewType);
};
