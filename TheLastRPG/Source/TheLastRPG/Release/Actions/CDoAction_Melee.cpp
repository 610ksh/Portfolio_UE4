#include "Release/Actions/CDoAction_Melee.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();
	CheckFalse(AttackDatas.Num() > 0);

	if (bEnableCombo)
	{
		bExistCombo = true;
		bEnableCombo = false;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	const FDoActionData& data = AttackDatas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bExistCombo);
	bExistCombo = false;

	OwnerCharacter->StopAnimMontage();
	ComboIndex++;

	const FDoActionData& data = AttackDatas[ComboIndex];
	CheckNull(data.AnimMontage);
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	const FDoActionData& data = AttackDatas[ComboIndex];
	OwnerCharacter->StopAnimMontage(data.AnimMontage);

	State->SetIdleMode();
	Status->SetMove();

	ComboIndex = 0;
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	CheckNull(InOtherCharacter);

	for (const ACharacter* other : HittedCharacters)
	{
		if (InOtherCharacter == other)
			return;
	}
	HittedCharacters.Add(InOtherCharacter);
	CLog::Log(InOtherCharacter->GetName() + "_BeginOverlap");

	/// Hit particle
	UParticleSystem* hitEffect = AttackDatas[ComboIndex].Effect;
	if (!!hitEffect)
	{
		FTransform transform = AttackDatas[ComboIndex].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	/// HitStop
	float hitStop = AttackDatas[ComboIndex].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1e-3f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStop * 1e-3f, false);
	}

	/// CameraShake
	TSubclassOf<UMatineeCameraShake> shake = AttackDatas[ComboIndex].ShakeClass;
	if (!!shake)
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->StartMatineeCameraShake(shake);

	FDamageEvent e;
	InOtherCharacter->TakeDamage(AttackDatas[ComboIndex].Power, e, OwnerCharacter->GetController(), this);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	// 쌍검일때 한쪽 검은 없을수도 있음.
	CheckNull(InOtherCharacter);
	CLog::Log(InOtherCharacter->GetName() + "_EndOverlap");
}

void ACDoAction_Melee::OnAttachmentCollision()
{

}

void ACDoAction_Melee::OffAttachmentCollision()
{
	HittedCharacters.Empty();
}

void ACDoAction_Melee::RestoreDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}