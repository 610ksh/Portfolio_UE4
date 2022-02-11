// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JG_CStatusComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API UJG_CStatusComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float WalkSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float RunSpeed = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float SprintSpeed = 600.0f;

public:
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

	FORCEINLINE bool CanMove() { return bCanMove; }

public:	
	// Sets default values for this actor's properties
	UJG_CStatusComponent();

	void SetMove();
	void SetStop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bCanMove = true;
};
