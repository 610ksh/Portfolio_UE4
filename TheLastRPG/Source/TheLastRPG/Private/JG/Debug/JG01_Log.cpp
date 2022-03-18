// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Debug/JG01_Log.h"
#include "JG/JG_Global.h"



// Sets default values
AJG01_Log::AJG01_Log()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJG01_Log::BeginPlay() //
{
	Super::BeginPlay();

	JG_Log::Print(10);

	JG_Log::Print(20, 1);
	JG_Log::Print(30, 2, 20.0f);
	JG_Log::Print(40, 2, 20.0f);

	JG_Log::Print("Unreal GamePlay");
	JG_Log::Print(GetActorLocation());
	JG_Log::Print(GetActorRotation());

	JG_Log::Log(55);
	JG_Log::Log(PI);
	JG_Log::Log("Unreal GamePlay");
	JG_Log::Log(GetActorLocation());
	JG_Log::Log(GetActorRotation());

	JG_Log::Log(this);
	JG_PrintLine();
}

// Called every frame
void AJG01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	JG_Log::Print(Time, 3);
}