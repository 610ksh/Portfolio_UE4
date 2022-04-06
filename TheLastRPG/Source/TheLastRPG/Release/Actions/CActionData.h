#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Release/Actions/CAction.h"
#include "CActionData.generated.h"

UCLASS()
class THELASTRPG_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment[0]; }
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }

	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
	FORCEINLINE int32 GetAttachmentCount() { return Attachment.Num(); }

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<TSubclassOf<class ACAttachment>> AttachmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData UnequipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

	class ACAttachment* GetAttachment(const int& idx);

private:
	TArray<class ACAttachment*> Attachment;
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;
};
