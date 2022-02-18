// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Actions/JG_CEquipment.h"
#include "JG/JG_Global.h"

#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/130_/Components/JG_CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AJG_CEquipment::AJG_CEquipment()
{

}

// Called when the game starts or when spawned
void AJG_CEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = JG_Helpers::GetComponent<UJG_CStateComponent>(OwnerCharacter);
	Status = JG_Helpers::GetComponent<UJG_CStatusComponent>(OwnerCharacter);

	//beginPlay가 블프를 호출하기 때문에 순서때문에 아래쪽에 배치함
	Super::BeginPlay();
	
}

