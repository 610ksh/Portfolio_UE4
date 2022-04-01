// CEquipment의 대부분 속성을 가져옴

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_CDoAction.generated.h"

UCLASS()
class THELASTRPG_API AJG_CDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJG_CDoAction();

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	class UJG_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
	class UJG_CStatusComponent* Status;
};
