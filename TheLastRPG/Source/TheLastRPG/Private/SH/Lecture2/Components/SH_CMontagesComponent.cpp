#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

USH_CMontagesComponent::USH_CMontagesComponent()
{

}


void USH_CMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CheckNull_SH(DataTable);

	TArray<FSH_MontageData*> datas;
	DataTable->GetAllRows<FSH_MontageData>("", datas);

	for (const FSH_MontageData* data : datas)
	{
		if (!!data)
		{
			//SH_CLog::Print(data->AnimMontage->GetPathName());
			SH_CLog::Log(data->AnimMontage->GetPathName());
		}
	}

	for (int32 i = 0; i < (int32)SH_EStateType::Max; ++i)
	{
		for (FSH_MontageData* data : datas) // �׼� ������
		{
			if ((SH_EStateType)i == data->Type) // Ÿ�� �����͸�
			{
				Datas[i] = data;

				continue;
			}
		} // for(data)
	}//for(i)
}

void USH_CMontagesComponent::PlayRoll()
{
	PlayAnimMontage(SH_EStateType::Roll);
}

void USH_CMontagesComponent::PlayBackstep()
{
	PlayAnimMontage(SH_EStateType::Backstep);
}

void USH_CMontagesComponent::PlayHitted()
{
	PlayAnimMontage(SH_EStateType::Hitted);
}

void USH_CMontagesComponent::PlayDead()
{
	PlayAnimMontage(SH_EStateType::Dead);
}

void USH_CMontagesComponent::PlayAnimMontage(SH_EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FSH_MontageData* data = Datas[(int32)InState];

	if (!!data)
	{
		if (!!data->AnimMontage)
		{
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
		}
	}
}

