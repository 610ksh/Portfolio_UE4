#include "Release/Components/CActionComponent.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCActionComponent::SetUnarmedMode()
{
	SetMode(ECountessActionType::Unarmed);
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
	{ // 같은 무기도 아니면서 이전과 다른 무기를 눌렀다면

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