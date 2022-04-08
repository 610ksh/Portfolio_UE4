// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Components/JG_CActionComponent.h"
#include "JG/JG_Global.h"

#include "JG/130_/Actions/JG_CActionData.h"
#include "JG/130_/Actions/JG_CAttachment.h"
#include "JG/130_/Actions/JG_CEquipment.h"

// Sets default values for this component's properties
UJG_CActionComponent::UJG_CActionComponent()
{

}



// Called when the game starts
void UJG_CActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
//
void UJG_CActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type]) 
	{
		
		AJG_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		JG_CheckNull(equipment);

		equipment->Unequip(); 
	}
	ChangeType(EActionType_JG::Unarmed);
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
	if (Type == InType) 
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false) 
	{
		
		AJG_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		JG_CheckNull(equipment);

		equipment->Unequip();
	}

	AJG_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	JG_CheckNull(equipment);

	equipment->Equip(); 

	ChangeType(InType);
}



void UJG_CActionComponent::ChangeType(EActionType_JG InNewType)
{
	
	EActionType_JG prevType = Type; // 성훈이가 말했던 부분
	Type = InNewType; 

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}