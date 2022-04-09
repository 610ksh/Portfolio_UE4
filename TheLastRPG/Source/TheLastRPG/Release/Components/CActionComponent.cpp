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
	{ // 현재 액션 타입에 대한 DataAsset이 존재한다면
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip(); // 장비 해제

		if (IsFistMode() || IsWarpMode() || IsFireStormMode()) 
		{ // Fist, Warp, FireStorm 애니메이션이 없어서 직접 불러줌
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

void UCActionComponent::SetFireStormMode()
{
	SetMode(EActionType::FireStorm);
}

void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType) // 같은 무기 2번 선택
	{
		SetUnarmedMode_Begin();
		return;
	}
	else if (IsUnarmedMode() == false)
	{ // 현재 Unarmed가 아니면서 && 이전과 다른 무기를 눌렀다면
		//ACEquipment* equipment = Datas[(int32)Type]->GetEquipment(); // 기존걸 벗고
		//CheckNull(equipment);
		//equipment->Unequip();

		/// 다른 장비를 끼려고 하면 지금 낀걸 넣으려고 함.
		SetUnarmedMode_Begin();
		return;
	}

	if (!!Datas[(int32)InType]) // 데이터가 없을 수도 있기 때문에
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