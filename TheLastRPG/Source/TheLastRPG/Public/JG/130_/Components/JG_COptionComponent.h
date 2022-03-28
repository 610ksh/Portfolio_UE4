// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JG_COptionComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API UJG_COptionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float HorizontalLookRate = 45;

	UPROPERTY(EditDefaultsOnly)
	float VecticalLookRate = 45;

public:
	FORCEINLINE float GetHorizontalLookRate() { return HorizontalLookRate; }
	FORCEINLINE float GetVecticalLookRate() { return VecticalLookRate; }
	
public:	
	// Sets default values for this component's properties
	UJG_COptionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
