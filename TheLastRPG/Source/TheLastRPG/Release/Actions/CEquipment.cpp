#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"

#include "GameFramework/Character.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Helpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = Helpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ACEquipment::Equip_Implementation()
{

}

void ACEquipment::Begin_Equip_Implementation()
{
	
}

void ACEquipment::End_Equip_Implementation()
{

}

void ACEquipment::Unequip_Implementation()
{

}