#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SH_CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData // 무기 장착관련 몽타주 데이터
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
};

UCLASS()
class THELASTRPG_API USH_CActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class ASH_CEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ASH_CDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class ASH_CAttachment* GetAttachment() { return Attachment; }

	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

public: /// 바깥 에디터에서 넣어줄 데이터 ★
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ASH_CEquipment* Equipment;
	class ASH_CAttachment* Attachment;
	class ASH_CDoAction* DoAction;
};
