#pragma once

#include "Release/Actions/CAction.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

UCLASS()
class THELASTRPG_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<TSubclassOf<class ACAttachment>> AttachmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> AttackDatas;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> SkillDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData UnequipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction);

private:
	FString GetLableName(class ACharacter* InOwnerCharacter, const FString& InName, const FString& InAttachmentClassName = "");
	FString GetAttachmentName(const FString& name);
};
