// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Components/JG_CActionComponent.h"
#include "JG/JG_Global.h"

// Sets default values for this component's properties
UJG_CActionComponent::UJG_CActionComponent()
{

}


// Called when the game starts
void UJG_CActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UJG_CActionComponent::SetUnarmedMode()
{
	SetMode(EActionType_JG::Unarmed);
}


void UJG_CActionComponent::SetOneHandMode()
{
	SetMode(EActionType_JG::OneHand);
}

void UJG_CActionComponent::SetTwoHandMode()
{
	SetMode(EActionType_JG::TwoHand);
}

void UJG_CActionComponent::SetMode(EActionType_JG InType)
{
	//if (Type == InType) 
	//{
	//	SetUnarmedMode();

	//	return;
	//}
	//else if (IsUnarmedMode() == false) 
	//{
	//	
	//	ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
	//	CheckNull(equipment);

	//	equipment->Unequip();
	//}

	//ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	//CheckNull(equipment);

	//equipment->Equip(); 

	//ChangeType(InType);
}



void UJG_CActionComponent::ChangeType(EActionType_JG InNewType)
{
	
	EActionType_JG prevType = Type; // 성훈이가 말했던 부분
	Type = InNewType; 

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}