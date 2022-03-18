#include "SH/Lecture2/Actions/SH_CDoAction_Melee.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

void ASH_CDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse_SH(Datas.Num() > 0); // �����Ͱ� ������ ����

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;

		return;
	}

	CheckFalse_SH(State->IsIdleMode()); // Idle��尡 �ƴ϶��(����)

	State->SetActionMode();

	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse_SH(bExist); // �޺� ������ ������ return
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

void ASH_CDoAction_Melee::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	CheckNull_SH(InOtherCharacter); // ���� ������ ����

	for (const ACharacter* other : HittedCharacters)
	{
		if (InOtherCharacter == other)
			return;
	}
	HittedCharacters.Add(InOtherCharacter);

	UParticleSystem* hitEffect = Datas[Index].Effect;
	if (!!hitEffect)
	{
		FTransform transform = Datas[Index].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}


	float hitStop = Datas[Index].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1e-3f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStop*1e-3f, false);
	}

	TSubclassOf<UMatineeCameraShake> shake = Datas[Index].ShakeClass;
	if (shake != NULL)
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->StartCameraShake(shake);// PlayCameraShake is deprecated

	FDamageEvent e;
	InOtherCharacter->TakeDamage(Datas[Index].Power, e, OwnerCharacter->GetController(), this); // ������ TakeDamage�� ������.
}


void ASH_CDoAction_Melee::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{

}

void ASH_CDoAction_Melee::OnAttachmentCollision()
{

}

void ASH_CDoAction_Melee::OffAttachmentCollision()
{
	HittedCharacters.Empty();
}

void ASH_CDoAction_Melee::RestoreDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f); // ���󺹱�
}