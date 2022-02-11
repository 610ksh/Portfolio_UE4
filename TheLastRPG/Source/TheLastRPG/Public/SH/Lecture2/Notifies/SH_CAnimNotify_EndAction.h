#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SH_CAnimNotify_EndAction.generated.h"

UCLASS()
class THELASTRPG_API USH_CAnimNotify_EndAction : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
