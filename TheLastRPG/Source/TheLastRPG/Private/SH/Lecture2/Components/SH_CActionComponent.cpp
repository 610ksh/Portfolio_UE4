#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Actions/SH_CAction.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
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
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(character, &Datas[i]);
	}
}

void USH_CActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void USH_CActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void USH_CActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void USH_CActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void USH_CActionComponent::SetFireStormMode()
{
	SetMode(EActionType::FireStorm);
}

void USH_CActionComponent::SetIceBallMode()
{
	SetMode(EActionType::IceBall);
}

void USH_CActionComponent::SetMode(EActionType InType)
{
	if (Type == InType) // ���� ���� ����
	{
		SetUnarmedMode(); // ���� ����

		return;
	}
	else if (IsUnarmedMode() == false) // �ٸ� ���� �������� ���¸�
	{
		/// TODO : ���� ��� �ٲٱ����� ���� �����ش�.
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull_SH(equipment);

		equipment->Unequip();
	}

	if (!!Datas[(int32)InType]) // �����Ͱ� ���� ���� �ֱ� ������
	{
		ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
		CheckNull_SH(equipment);

		equipment->Equip(); // ��� ����
	}

	ChangeType(InType);
}

void USH_CActionComponent::ChangeType(EActionType InNewType)
{
	/// Q. �Ʒ� InNewType���� �ϴ���, Type���� �̸� �����صδ°� ���� �ʳ�?
	EActionType prevType = Type; // ���Ǵ� InNewType�̾���.
	Type = InNewType; // ���Ӱ� ����

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void USH_CActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type]) // ���� �������� ���Ⱑ �����Ѵٸ�
	{
		// ���� �ڽ��� Ÿ���� ��� ���� ActionData ������ �����´�.
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull_SH(equipment);

		equipment->Unequip(); // Unequip�� Ǯ���ش�. 
	}

	/*
	- 2022. February 15. 169�� ���� �κп��� ���� �߰�. �Ʒ� ������ ��� ������.
	- Unaramed �����϶� equip�� �ʿ䰡 ���� ����.
	*/
	//// Enemy�� �Ȱ��� �����ϹǷ� ��������. �÷��̾�� Enemy ��� ���������� Ȯ���ؾ���. �ַ� DA(������ �ּ�)�� �־��ٶ� ����
	//ASH_CEquipment* equipment = Datas[(int32)EActionType::Unarmed]->GetEquipment(); // ���⼭ �� ����.
	//CheckNull(equipment);
	//
	//equipment->Equip(); // Unarmed�� ����


	ChangeType(EActionType::Unarmed);
}

void USH_CActionComponent::DoAction()
{
	CheckTrue_SH(IsUnarmedMode()); // ���⸦ ���� �ʾ������� ���

	if (!!Datas[(int32)Type])
	{
		ASH_CDoAction* action = Datas[(int32)Type]->GetDoAction(); // ������ Action ������Ʈ ���͸� ������

		if (!!action)
			action->DoAction();
	}
}

void USH_CActionComponent::DoAim()
{
	SetAimMode(true);
}

void USH_CActionComponent::UndoAim()
{
	SetAimMode(false);
}

void USH_CActionComponent::SetAimMode(bool InAim)
{
	CheckTrue_SH(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ASH_CDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			InAim ? action->OnAim() : action->OffAim();
	}
}

void USH_CActionComponent::OffAllCollision()
{
	for (USH_CAction* data : Datas)
	{
		if (!!data == false)
			continue;
		if (!!data->GetAttachment() == false)
			continue;

		data->GetAttachment()->OffCollision();
	}
}

void USH_CActionComponent::DestroyAllActions()
{
	for (USH_CAction* data : Datas)
	{
		if (!!data == false)
			continue;

		if (!!data->GetAttachment())
			data->GetAttachment()->Destroy();
		if (!!data->GetEquipment())
			data->GetEquipment()->Destroy();
		if (!!data->GetDoAction())
			data->GetDoAction()->Destroy();
	}
}