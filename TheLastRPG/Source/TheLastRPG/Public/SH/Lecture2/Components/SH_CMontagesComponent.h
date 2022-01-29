#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "Engine/DataTable.h"
#include "SH_CMontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type; // enum�� ���漱���� �ȵ�.

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

public:	
	USH_CMontagesComponent();

protected:
	virtual void BeginPlay() override;

};
