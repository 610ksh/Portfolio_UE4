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
	if (Type == InType) // ���� ���� 2�� ����
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{ // ���� ���⵵ �ƴϸ鼭 ������ �ٸ� ���⸦ �����ٸ�

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