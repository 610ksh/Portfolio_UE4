#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

/// Data for Equip, Unequip
USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

/// Action data for Attack
USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.0f;

	UPROPERTY(EditAnywhere)
		float HitStop; // 타격감을 위한 경직

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMatineeCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASH_CThrow> ThrowClass;
};

UCLASS()
class THELASTRPG_API UCAction : public UObject
{
	GENERATED_BODY()
	
public:
	friend class UCActionData;

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment[0]; }
	FORCEINLINE class ACAttachment* GetAttachment(const int& idx) { return Attachment[idx]; }
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }

	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
	FORCEINLINE int32 GetAttachmentCount() { return AttachCount; }

private:
	class ACAttachment* Attachment[2];
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;

	FLinearColor EquipmentColor;
	int32 AttachCount;
};
