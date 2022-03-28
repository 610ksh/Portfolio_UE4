#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Release/Components/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FCountessMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECountessStateType Type;
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

protected:
	virtual void BeginPlay() override;

private:
	FCountessMontageData* Datas[(int32)ECountessStateType::Max];

};
