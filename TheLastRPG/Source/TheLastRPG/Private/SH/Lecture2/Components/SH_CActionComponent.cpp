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
	for (int32 i = 0; i < (int32)ESH_ActionType::Max; ++i)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(character, &Datas[i]);
	}
}

void USH_CActionComponent::SetFistMode()
{
	SetMode(ESH_ActionType::Fist);
}

void USH_CActionComponent::SetOneHandMode()
{
	SetMode(ESH_ActionType::OneHand);
}

void USH_CActionComponent::SetTwoHandMode()
{
	SetMode(ESH_ActionType::TwoHand);
}

void USH_CActionComponent::SetWarpMode()
{
	SetMode(ESH_ActionType::Warp);
}

void USH_CActionComponent::SetFireStormMode()
{
	SetMode(ESH_ActionType::FireStorm);
}

void USH_CActionComponent::SetIceBallMode()
{
	SetMode(ESH_ActionType::IceBall);
}

void USH_CActionComponent::SetMode(ESH_ActionType InType)
{
	if (Type == InType) // 같은 무기 장착
	{
		SetUnarmedMode(); // 무기 해제

		return;
	}
	else if (IsUnarmedMode() == false) // 다른 무기 장착중인 상태면
	{
		/// TODO : 현재 장비를 바꾸기전에 먼저 벗겨준다.
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		SH_CheckNull(equipment);

		equipment->Unequip();
	}

	if (!!Datas[(int32)InType]) // 데이터가 없을 수도 있기 때문에
	{
		ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
		SH_CheckNull(equipment);

		equipment->Equip(); // 장비 장착
	}

	ChangeType(InType);
}

void USH_CActionComponent::ChangeType(ESH_ActionType InNewType)
{
	/// Q. 아래 InNewType으로 하던데, Type으로 미리 저장해두는게 맞지 않나?
	ESH_ActionType prevType = Type; // 강의는 InNewType이었음.
	Type = InNewType; // 새롭게 수정

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void USH_CActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type]) // 현재 장착중인 무기가 존재한다면
	{
		// 현재 자신의 타입의 장비에 대한 ActionData 정보를 가져온다.
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		SH_CheckNull(equipment);

		equipment->Unequip(); // Unequip로 풀어준다. 
	}

	/*
	- 2022. February 15. 169강 시작 부분에서 오류 발견. 아래 내용을 모두 지워줌.
	- Unaramed 상태일때 equip할 필요가 없기 때문.
	*/
	//// Enemy도 똑같이 동작하므로 주의하자. 플레이어와 Enemy 모두 문제없는지 확인해야함. 주로 DA(데이터 애셋)을 넣어줄때 터짐
	//ASH_CEquipment* equipment = Datas[(int32)EActionType::Unarmed]->GetEquipment(); // 여기서 잘 터짐.
	//CheckNull(equipment);
	//
	//equipment->Equip(); // Unarmed로 장착


	ChangeType(ESH_ActionType::Unarmed);
}

void USH_CActionComponent::DoAction()
{
	SH_CheckTrue(IsUnarmedMode()); // 무기를 들지 않았을때만 통과

	if (!!Datas[(int32)Type])
	{
		ASH_CDoAction* action = Datas[(int32)Type]->GetDoAction(); // 생성한 Action 컴포넌트 액터를 가져옴

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
	SH_CheckTrue(IsUnarmedMode());

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