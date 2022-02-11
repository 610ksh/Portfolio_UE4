#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SH_CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData // ���� �������� ��Ÿ�� ������
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
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.0f;

	UPROPERTY(EditAnywhere)
		float HitStop; // Ÿ�ݰ��� ���� ����

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

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CEquipment> EquipmentClass; // �ٱ� �����Ϳ��� �־��ٰ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData; // �ٱ� �����Ϳ��� �־��ٰ���

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
