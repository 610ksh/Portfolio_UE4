#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

USH_CActionComponent::USH_CActionComponent()
{

}

void USH_CActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; ++i)
	{
		if (!!Datas[i])
			Datas[i]->BeginPlay(character);
	}
}

void USH_CActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
	{
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip();
	}

	ChangeType(EActionType::Unarmed);
}

void USH_CActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void USH_CActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void USH_CActionComponent::SetMode(EActionType InType)
{
	if (Type == InType) // ���� ���� ����
	{
		SetUnarmedMode(); // ���� ����

		return;
	}
	else if (IsUnarmedMode() == false) // �ٸ� ���� ����
	{
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	CheckNull(equipment);

	equipment->Equip();

	ChangeType(InType);
}

void USH_CActionComponent::ChangeType(EActionType InNewType)
{
	/// Q. �Ʒ� InNewType���� �ϴ���, Type���� �̸� �����صδ°� ���� �ʳ�?
	EActionType prevType = InNewType; // ���Ǵ� InNewType�̾���.
	Type = InNewType; // ���Ӱ� ����

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}