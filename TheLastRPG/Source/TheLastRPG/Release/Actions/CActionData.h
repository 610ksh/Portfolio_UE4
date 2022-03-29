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
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ACEquipment* Equipment;
};
