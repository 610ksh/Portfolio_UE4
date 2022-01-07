// Fill out your copyright notice in the Description page of Project Settings.


#include "SH/Actor/SH_Spawner.h"
#include "SH/Global_SH.h"
#include "SH/Actor/SH_SpawnActor.h"

// Sets default values
ASH_Spawner::ASH_Spawner()
{

}

// Called when the game starts or when spawned
void ASH_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < 3; ++i)
	{
		FTransform transform;
		FVector location = GetActorLocation();
		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));

		SpawnActors[i] = GetWorld()->SpawnActor<ASH_SpawnActor>(SpawnClass[i], transform);

		//FVector location = GetActorLocation();
		//SpawnActors[i]->SetActorLocation(FVector(location.X + i * 400, location.Y, location.Z));
	}
}