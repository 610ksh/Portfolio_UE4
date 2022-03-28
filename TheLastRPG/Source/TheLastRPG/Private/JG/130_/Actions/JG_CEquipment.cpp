// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Actions/JG_CEquipment.h"
#include "JG/JG_Global.h"

#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/130_/Components/JG_CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
//
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

void AJG_CEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (Data.AnimMontage != NULL)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRatio, Data.StartSection);
	else
		End_Equip();


		OwnerCharacter->bUseControllerRotationYaw = true; 
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false; 
	
}

void AJG_CEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void AJG_CEquipment::End_Equip_Implementation()
{
	bEquipped = true;

	State->SetIdleMode();
}

void AJG_CEquipment::Unequip_Implementation()
{
	bEquipped = false;

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

