// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_DrawDebug.generated.h"

UCLASS()
class THELASTRPG_API ASH_DrawDebug : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FVector InitLocation[5];

	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FBox Box;

	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FTransform Transform;

public:	
	// Sets default values for this actor's properties
	ASH_DrawDebug();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector Location[5];

};
