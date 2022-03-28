#include "Release/Components/CStateComponent.h"
#include "Release/Global.h"

UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::SetIdleMode()
{
	ChangeType(ECountessStateType::Idle);
}

void UCStateComponent::SetRollMode()
{
	ChangeType(ECountessStateType::Roll);
}

void UCStateComponent::SetBackstepMode()
{
	ChangeType(ECountessStateType::Backstep);
}

void UCStateComponent::ChangeType(ECountessStateType InType)
{
	ECountessStateType prevType = Type;
	Type = InType;

	if (OnCountessStateTypeChanged.IsBound())
		OnCountessStateTypeChanged.Broadcast(prevType, InType);
}