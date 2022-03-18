// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/JG_Global.h"

// Sets default values for this component's properties
UJG_CStateComponent::UJG_CStateComponent()
{

}


// Called when the game starts
void UJG_CStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UJG_CStateComponent::SetIdleMode()
{
	ChangeType(EStateType_JG::Idle);
}

void UJG_CStateComponent::SetRollMode()
{
	ChangeType(EStateType_JG::Roll);
}

void UJG_CStateComponent::SetBackstepMode()
{
	ChangeType(EStateType_JG::Backstep);
}

void UJG_CStateComponent::SetEquipMode()
{
	ChangeType(EStateType_JG::Equip);
}
//
void UJG_CStateComponent::SetActionMode()
{
	ChangeType(EStateType_JG::Action);
}


void UJG_CStateComponent::ChangeType(EStateType_JG InType)
{
	EStateType_JG type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(type, InType);
	}
}