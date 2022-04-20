#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/Lecture2/SH_ICharacter.h"
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

	if (Data.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true; // ���콺 ȸ���� ���� ī�޶� ���� ����.
		// ȸ�� �������� ĳ���� �޽ð� ���� ���Ѵ�. �޽ô� �׻� ����
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false; // �޽ø� ���� ���ϰ���
	}

	/// ���� ������ ���� ����
	ISH_ICharacter* character = Cast<ISH_ICharacter>(OwnerCharacter);
	SH_CheckNull(character);
	character->ChangeColor(Color);
}

void ASH_CEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ASH_CEquipment::End_Equip_Implementation()
{
	bEquipped = true;

	State->SetIdleMode();
}

void ASH_CEquipment::Unequip_Implementation()
{
	bEquipped = false;

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}
