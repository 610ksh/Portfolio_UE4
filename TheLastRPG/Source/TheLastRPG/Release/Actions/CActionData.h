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
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData UnequipmentData;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ACAttachment* Attachment;
	class ACEquipment* Equipment;
};
