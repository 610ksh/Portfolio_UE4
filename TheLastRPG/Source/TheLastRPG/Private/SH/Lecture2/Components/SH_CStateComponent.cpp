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
	SH_CLog::Print("SetIdleMode");
	ChangeType(EStateType::Idle);
}

void USH_CStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void USH_CStateComponent::SetBackstepMode()
{
	ChangeType(EStateType::Backstep);
}

void USH_CStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void USH_CStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void USH_CStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}


void USH_CStateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(type, InType);
	}
}