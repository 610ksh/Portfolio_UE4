// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Spawner.generated.h"

UCLASS()
class THELASTRPG_API ASH_Spawner : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ASH_SpawnActor> SpawnClass[3];

public:	
	// Sets default values for this actor's properties
	ASH_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ASH_SpawnActor* SpawnActors[3];
};
