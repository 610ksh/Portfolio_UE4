#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SH/Lecture2/Actions/SH_CAction.h" // for FEquipmentData
#include "SH_CActionData.generated.h"

UCLASS()
class THELASTRPG_API USH_CActionData : public UDataAsset
{
	GENERATED_BODY()
	
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
	void BeginPlay(class ACharacter* InOwnerCharacter, class USH_CAction** OutAction);

private:
	FString GetLableName(class ACharacter* InOwnerCharacter, FString InName);

};
