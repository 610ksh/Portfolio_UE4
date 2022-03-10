// Fill out your copyright notice in the Description page of Project Settings.


#include "YH/ActionRPG/Characters/YH_CActionPlayer.h"

// Sets default values
AYH_CActionPlayer::AYH_CActionPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYH_CActionPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYH_CActionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYH_CActionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

