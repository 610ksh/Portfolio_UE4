#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ASH_CEquipment::ASH_CEquipment()
{

}

void ASH_CEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = SH_CHelpers::GetComponent<USH_CStateComponent>(OwnerCharacter);
	Status = SH_CHelpers::GetComponent<USH_CStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ASH_CEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (Data.AnimMontage != NULL)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRatio, Data.StartSection);
	else
		End_Equip();

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ASH_CEquipment::Unequip_Implementation()
{
	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ASH_CEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ASH_CEquipment::End_Equip_Implementation()
{
	State->SetIdleMode();
}
