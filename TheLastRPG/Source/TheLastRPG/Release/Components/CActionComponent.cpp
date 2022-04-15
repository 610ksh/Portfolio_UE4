#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CAction.h"
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
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(character, &Datas[i]);
	}
}

void UCActionComponent::SetUnarmedMode_Begin()
{
	if (!!DataAssets[(int32)Type])
	{ // ���� �׼� Ÿ�Կ� ���� DataAsset�� �����Ѵٸ�
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip(); // ��� ����

		if (IsFistMode() || IsWarpMode() || IsFireStormMode() || IsThrowMode())
		{ // Fist, Warp, FireStorm �ִϸ��̼��� ��� ���� �ҷ���
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
	equipment->ChangeColor();
}

void UCActionComponent::SetFistMode()
{
	CheckNull(Datas[(int32)EActionType::Fist]);
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	CheckNull(Datas[(int32)EActionType::OneHand]);
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	CheckNull(Datas[(int32)EActionType::TwoHand]);
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetWarpMode()
{
	CheckNull(Datas[(int32)EActionType::Warp]);
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetFireStormMode()
{
	CheckNull(Datas[(int32)EActionType::FireStorm]);
	SetMode(EActionType::FireStorm);
}

void UCActionComponent::SetThrowMode()
{
	CheckNull(Datas[(int32)EActionType::Throw]);
	SetMode(EActionType::Throw);
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

void UCActionComponent::DoSkillAction(ESkillType InType)
{
	CheckTrue(IsUnarmedMode());

	ACDoAction* action = Datas[(int32)Type]->GetDoAction();
	CheckNull(action);

	switch (InType)
	{
	case ESkillType::Q:
		action->DoSkill_Q();
		break;
	case ESkillType::E:
		action->DoSkill_E();
		break;
	case ESkillType::R:
		action->DoSkill_R();
		break;
	case ESkillType::F:
		action->DoSkill_F();
		break;
	default:
		break;
	}
}

void UCActionComponent::DoAim()
{
	SetAimMode(true);
}

void UCActionComponent::UndoAim()
{
	SetAimMode(false);
}

void UCActionComponent::SetAimMode(bool InAim)
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();
		if (!!action)
			InAim ? action->OnAim() : action->OffAim();
	}
}