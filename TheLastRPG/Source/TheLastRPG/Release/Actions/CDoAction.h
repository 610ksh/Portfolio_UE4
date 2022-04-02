#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Release/Actions/CAction.h"
#include "CDoAction.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetDatas(const TArray<FDoActionData>& InDatas) { Datas = InDatas; }
	
public:	
	ACDoAction();

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

protected:
	TArray<FDoActionData> Datas;
};
