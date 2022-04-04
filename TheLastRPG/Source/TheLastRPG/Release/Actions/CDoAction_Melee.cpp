#include "Release/Actions/CDoAction_Melee.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);

	if (bEnableCombo)
	{
		bExistCombo = true;
		bEnableCombo = false;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bExistCombo);
	bExistCombo = false;

	OwnerCharacter->StopAnimMontage();
	comboIndex++;

	const FDoActionData& data = Datas[comboIndex];
	CheckNull(data.AnimMontage);
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	const FDoActionData& data = Datas[comboIndex];
	OwnerCharacter->StopAnimMontage();

	State->SetIdleMode();
	Status->SetMove();

	comboIndex = 0;
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	CheckNull(InOtherCharacter);
	CLog::Log(InOtherCharacter->GetName() + "_BeginOverlap");

	FDamageEvent e;
	InOtherCharacter->TakeDamage(Datas[comboIndex].Power, e, OwnerCharacter->GetController(), this);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	CLog::Log(InOtherCharacter->GetName() + "_EndOverlap");
}