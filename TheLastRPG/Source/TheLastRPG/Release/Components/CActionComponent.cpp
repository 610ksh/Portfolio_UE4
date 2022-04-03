#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)ECountessActionType::Max; ++i)
	{
		if (!!Datas[i])
			Datas[i]->BeginPlay(character);
	}
}

void UCActionComponent::SetUnarmedMode_Begin()
{
	if (!!Datas[(int32)Type])
	{ // ���� �׼� Ÿ�Կ� ���� DataAsset�� �����Ѵٸ�
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip(); // ��� ����
	}
}

/// Notice : SetUnarmedMode function called notify
void UCActionComponent::SetUnarmedMode()
{ 
	ChangeType(ECountessActionType::Unarmed);

	CheckNull(Datas[(int32)Type]);
	ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
	CheckNull(equipment);
	equipment->ChangeColor();
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(ECountessActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(ECountessActionType::TwoHand);
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoAction();
	}
}

void UCActionComponent::SetMode(ECountessActionType InType)
{
	if (Type == InType) // ���� ���� 2�� ����
	{
		SetUnarmedMode_Begin();
		return;
	}
	else if (IsUnarmedMode() == false)
	{ // ���� Unarmed�� �ƴϸ鼭 && ������ �ٸ� ���⸦ �����ٸ�
		//ACEquipment* equipment = Datas[(int32)Type]->GetEquipment(); // ������ ����
		//CheckNull(equipment);
		//equipment->Unequip();
	}

	if (!!Datas[(int32)InType]) // �����Ͱ� ���� ���� �ֱ� ������
	{
		ACEquipment* equipment = Datas[(int32)InType]->GetEquipment();
		CheckNull(equipment);
		equipment->Equip();
	}

	ChangeType(InType);
}

void UCActionComponent::ChangeType(ECountessActionType InNewType)
{
	ECountessActionType prevType = Type;
	Type = InNewType;

	if (OnCountessActionTypeChanged.IsBound())
		OnCountessActionTypeChanged.Broadcast(prevType, InNewType);
}