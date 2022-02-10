#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
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
		if (!!Datas[i])
			Datas[i]->BeginPlay(character);
	}
}

void USH_CActionComponent::SetMode(EActionType InType)
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
		CheckNull(equipment);

		equipment->Unequip();
	}

	ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	CheckNull(equipment);

	equipment->Equip(); // 장비 장착

	ChangeType(InType);
}

void USH_CActionComponent::ChangeType(EActionType InNewType)
{
	/// Q. 아래 InNewType으로 하던데, Type으로 미리 저장해두는게 맞지 않나?
	EActionType prevType = Type; // 강의는 InNewType이었음.
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
		CheckNull(equipment);

		equipment->Unequip(); // Unequip로 풀어준다. 
	}

	ASH_CEquipment* equipment = Datas[(int32)EActionType::Unarmed]->GetEquipment(); // 여기서 잘 터짐.
	CheckNull(equipment);
	
	equipment->Equip(); // Unarmed로 장착

	ChangeType(EActionType::Unarmed);
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

void USH_CActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode()); // 무기를 들지 않았을때만 통과

	if (!!Datas[(int32)Type])
	{
		ASH_CDoAction* action = Datas[(int32)Type]->GetDoAction(); // 생성한 Action 컴포넌트 액터를 가져옴

		if (!!action)
			action->DoAction();
	}
}

