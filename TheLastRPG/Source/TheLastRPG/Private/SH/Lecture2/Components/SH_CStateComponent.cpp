#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/SH_Global.h"

USH_CStateComponent::USH_CStateComponent()
{

}

void USH_CStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USH_CStateComponent::SetIdleMode()
{
	ChangeType(SH_EStateType::Idle);
}

void USH_CStateComponent::SetRollMode()
{
	ChangeType(SH_EStateType::Roll);
}

void USH_CStateComponent::SetBackstepMode()
{
	ChangeType(SH_EStateType::Backstep);
}

void USH_CStateComponent::SetEquipMode()
{
	ChangeType(SH_EStateType::Equip);
}

void USH_CStateComponent::SetActionMode()
{
	ChangeType(SH_EStateType::Action);
}

void USH_CStateComponent::SetHittedMode()
{
	ChangeType(SH_EStateType::Hitted);
}

void USH_CStateComponent::SetDeadMode()
{
	ChangeType(SH_EStateType::Dead);
}

void USH_CStateComponent::ChangeType(SH_EStateType InType)
{
	SH_EStateType prevType = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(prevType, InType);
	}
}