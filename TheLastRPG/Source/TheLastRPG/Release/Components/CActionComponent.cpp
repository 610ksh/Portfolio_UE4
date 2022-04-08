#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CActionData.h"
#include "Release/Actions/CDoAction.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EActionType::Max; ++i)
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

		if (IsFistMode()) 
		{ // Fist�� �ִϸ��̼��� ��� ���� �ҷ���
			SetUnarmedMode();
			return;
		}
	}
}

/// Notice : SetUnarmedMode function called notify
void UCActionComponent::SetUnarmedMode()
{ 
	ChangeType(EActionType::Unarmed);

	CheckNull(Datas[(int32)Type]);
	ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
	CheckNull(equipment);
	equipment->ChangeColor();
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetMode(EActionType InType)
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

		/// �ٸ� ��� ������ �ϸ� ���� ���� �������� ��.
		SetUnarmedMode_Begin();
		return;
	}

	if (!!Datas[(int32)InType]) // �����Ͱ� ���� ���� �ֱ� ������
	{
		ACEquipment* equipment = Datas[(int32)InType]->GetEquipment();
		CheckNull(equipment);
		equipment->Equip();
	}

	ChangeType(InType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

/// Attack
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