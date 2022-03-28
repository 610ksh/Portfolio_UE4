#include "Release/Components/CMontageComponent.h"
#include "Release/Global.h"

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
}