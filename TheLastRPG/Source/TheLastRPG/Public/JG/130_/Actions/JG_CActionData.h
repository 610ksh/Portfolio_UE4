// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JG_CActionData.generated.h"


USTRUCT(BlueprintType)
struct FEquipmentData_JG
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



UCLASS()
class THELASTRPG_API UJG_CActionData : public UDataAsset
{
	GENERATED_BODY()
	
	
public:
	FORCEINLINE class AJG_CEquipment* GetEquipment() { return Equipment; }

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class AJG_CAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class AJG_CEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData_JG EquipmentData;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);


private:
	class AJG_CEquipment* Equipment;
	class AJG_CAttachment* Attachment;
};
