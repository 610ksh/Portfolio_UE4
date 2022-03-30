#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Unequip.generated.h"

UCLASS()
class THELASTRPG_API UCAnimNotifyState_Unequip : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

};
