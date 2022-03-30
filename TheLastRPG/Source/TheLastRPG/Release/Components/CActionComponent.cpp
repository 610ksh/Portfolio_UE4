#include "Release/Components/CActionComponent.h"
#include "Release/Actions/CActionData.h"
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

void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type]) 
	{ // 현재 액션 타입에 대한 DataAsset이 존재한다면
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip(); // 장비 해제
	}

	ChangeType(ECountessActionType::Unarmed);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(ECountessActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(ECountessActionType::TwoHand);
}

void UCActionComponent::SetMode(ECountessActionType InType)
{
	if (Type == InType) // 같은 무기 2번 선택
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{ // 현재 Unarmed가 아니면서 && 이전과 다른 무기를 눌렀다면
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment(); // 기존걸 벗고
		CheckNull(equipment);
		equipment->Unequip();
	}

	ACEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	CheckNull(equipment);
	equipment->Equip();

	ChangeType(InType);
}

void UCActionComponent::ChangeType(ECountessActionType InNewType)
{
	ECountessActionType prevType = Type;
	Type = InNewType;

	if (OnCountessActionTypeChanged.IsBound())
		OnCountessActionTypeChanged.Broadcast(prevType, InNewType);
}