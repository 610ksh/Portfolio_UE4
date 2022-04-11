// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Components/JG_CMontagesComponent.h"
#include "JG/JG_Global.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UJG_CMontagesComponent::UJG_CMontagesComponent()
{

}





// Called when the game starts
void UJG_CMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	JG_CheckNull(DataTable);

	TArray<FMontageData_JG*> datas;
	DataTable->GetAllRows<FMontageData_JG>("", datas);

	//for (const FMontageData_JG* data : datas)
	//{
	//	if (!!data)
	//		JG_Log::Print(data->AnimMontage->GetPathName());
	//}


	// 이해가 쉽지 않음
	for(int32 i=0; i<(int32)EStateType_JG::Max; i++)
		for(FMontageData_JG* data : datas)
			if ((EStateType_JG)i == data->Type)
			{
				Datas[i] = data;
				continue;
			}
}

void UJG_CMontagesComponent::PlayRoll()
{
	PlayAnimMontage(EStateType_JG::Roll);

}

void UJG_CMontagesComponent::PlayBackstep()
{
	PlayAnimMontage(EStateType_JG::Backstep);

}


void UJG_CMontagesComponent::PlayAnimMontage(EStateType_JG InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FMontageData_JG* data = Datas[(int32)InState];

	if (!!data)
	{
		if (!!data->AnimMontage)
		{
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
		}
	}
}


