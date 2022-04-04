#include "Release/Components/CMontageComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CheckNull(DataTable);

	TArray<FCountessMontageData*> datas;
	DataTable->GetAllRows<FCountessMontageData>("", datas);

	for (const FCountessMontageData* data : datas)
	{
		if (!!data)
			CLog::Log(data->AnimMontage->GetPathName());
			CLog::Print(data->AnimMontage->GetPathName());
	}

	// find Montage data, O(n^2)
	for (int32 i = 0; i < (int32)EStateType::Max; ++i)
	{
		for (FCountessMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;
				continue;
			}
		}
	}
}

void UCMontageComponent::PlayAnimMontage(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	const FCountessMontageData* data = Datas[(int32)InState];

	if (!!data)
	{
		if (!!data->AnimMontage)
		{
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
		}
	}
}

void UCMontageComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::Roll);
}

void UCMontageComponent::PlayBackstep()
{
	PlayAnimMontage(EStateType::Backstep);
}