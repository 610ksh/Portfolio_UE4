// Fill out your copyright notice in the Description page of Project Settings.
#include "JG/130_/Components/JG_CStatusComponent.h"
#include "JG/JG_Global.h"

//
// Sets default values
UJG_CStatusComponent::UJG_CStatusComponent()
{

}


// Called when the game starts or when spawned
void UJG_CStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}



void UJG_CStatusComponent::SetMove()
{
	bCanMove = true;
}

void UJG_CStatusComponent::SetStop()
{
	bCanMove = false;
}