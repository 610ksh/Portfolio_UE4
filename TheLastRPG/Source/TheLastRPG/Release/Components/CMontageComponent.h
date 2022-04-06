#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Release/Components/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;
	UPROPERTY(EditAnywhere)
		FName StartSection;
};

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

public:	
	UCMontageComponent();

	void PlayRoll();
	void PlayBackstep();
	void PlayHitted();

protected:
	virtual void BeginPlay() override;

private:
	void PlayAnimMontage(EStateType InState);

private:
	FMontageData* Datas[(int32)EStateType::Max];

};
