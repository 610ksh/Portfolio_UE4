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
		OwnerCharacter->bUseControllerRotationYaw = true; // 마우스 회전에 따라 카메라도 같이 돈다.
		// 회전 방향으로 캐릭터 메시가 돌지 못한다. 메시는 항상 정면
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false; // 메시를 돌지 못하게함
	}

	/// 무기 장착시 색상 변경
	ISH_ICharacter* character = Cast<ISH_ICharacter>(OwnerCharacter);
	CheckNull(character);
	character->ChangeColor(Color);
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

void ASH_CEquipment::Unequip_Implementation()
{
	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}
