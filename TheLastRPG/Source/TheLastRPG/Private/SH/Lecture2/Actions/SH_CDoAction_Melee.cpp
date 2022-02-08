#include "SH/Lecture2/Actions/SH_CDoAction_Melee.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

void ASH_CDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0); // 데이터가 있다면

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;

		return;
	}

	CheckFalse(State->IsIdleMode());

	State->SetActionMode();

	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();
	CheckFalse(bExist); // 콤보 공격이 없으면 return
	bExist = false;

	OwnerCharacter->StopAnimMontage();
	Index++;

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_Melee::End_DoActin()
{
	Super::End_DoActin();

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->StopAnimMontage(data.AnimMontage);

	State->SetIdleMode();
	Status->SetMove();

	Index = 0;
}
