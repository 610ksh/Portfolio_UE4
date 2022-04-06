#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "Engine/DataTable.h"
#include "SH_CMontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FSH_MontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		SH_EStateType Type; // enum�� ���漱���� �ȵ�.

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

	void PlayRoll();
	void PlayBackstep();
	void PlayHitted();
	void PlayDead();

protected:
	virtual void BeginPlay() override;

private:
	void PlayAnimMontage(SH_EStateType InState);

private:
	FSH_MontageData* Datas[(int32)SH_EStateType::Max];
};
