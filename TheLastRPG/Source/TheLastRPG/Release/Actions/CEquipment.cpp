#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	State->SetEquipMode();

	if (EquipData.AnimMontage != NULL) // if any montage has, play equip montage
		OwnerCharacter->PlayAnimMontage(EquipData.AnimMontage, EquipData.PlayRatio, EquipData.StartSection);
	else
		End_Equip();

	/// player don't rotate when character equip
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	State->SetIdleMode();
}

void ACEquipment::Unequip_Implementation()
{
	State->SetUnequipMode();

	if (UnequipData.AnimMontage != NULL) // if any montage has, play equip montage
		OwnerCharacter->PlayAnimMontage(UnequipData.AnimMontage, UnequipData.PlayRatio, UnequipData.StartSection);
	else
		End_Unequip();
}

void ACEquipment::Begin_Unequip_Implementation()
{
	
}

void ACEquipment::End_Unequip_Implementation()
{
	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	State->SetIdleMode();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}