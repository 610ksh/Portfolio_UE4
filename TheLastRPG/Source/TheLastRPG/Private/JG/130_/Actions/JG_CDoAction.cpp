// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Actions/JG_CDoAction.h"
#include "JG/JG_Global.h"

#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/130_/Components/JG_CStatusComponent.h"

#include "GameFramework/Character.h"

// Sets default values
AJG_CDoAction::AJG_CDoAction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJG_CDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = JG_Helpers::GetComponent<UJG_CStateComponent>(OwnerCharacter);
	Status = JG_Helpers::GetComponent<UJG_CStatusComponent>(OwnerCharacter);

	//beginPlay가 블프를 호출하기 때문에 순서때문에 아래쪽에 배치함
	Super::BeginPlay();
	
}

// Called every frame
void AJG_CDoAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

