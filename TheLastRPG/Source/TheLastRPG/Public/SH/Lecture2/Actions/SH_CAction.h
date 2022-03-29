#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Release/Actions/CAction.h"
#include "SH_CAction.generated.h"

//USTRUCT(BlueprintType)
//struct FEquipmentData // 무기 장착관련 몽타주 데이터
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere)
//		class UAnimMontage* AnimMontage;
//
//	UPROPERTY(EditAnywhere)
//		float PlayRatio = 1.0f;
//
//	UPROPERTY(EditAnywhere)
//		FName StartSection;
//
//	UPROPERTY(EditAnywhere)
//		bool bCanMove = true;
//
//	UPROPERTY(EditAnywhere)
//		bool bPawnControl = true;
//};
//
//USTRUCT(BlueprintType)
//struct FDoActionData : public FEquipmentData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere)
//		float Power = 5.0f;
//
//	UPROPERTY(EditAnywhere)
//		float HitStop; // 타격감을 위한 경직
//
//	UPROPERTY(EditAnywhere)
//		class UParticleSystem* Effect;
//
//	UPROPERTY(EditAnywhere)
//		FTransform EffectTransform;
//
//	UPROPERTY(EditAnywhere)
//		TSubclassOf<class UMatineeCameraShake> ShakeClass;
//
//	UPROPERTY(EditAnywhere)
//		TSubclassOf<class ASH_CThrow> ThrowClass;
//};

UCLASS()
class THELASTRPG_API USH_CAction : public UCAction
{
	GENERATED_BODY()

public:
	friend class USH_CActionData;

public:
	FORCEINLINE class ASH_CEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ASH_CDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class ASH_CAttachment* GetAttachment() { return Attachment; }

	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

private:
	class ASH_CEquipment* Equipment;
	class ASH_CAttachment* Attachment;
	class ASH_CDoAction* DoAction;

	FLinearColor EquipmentColor;
};
