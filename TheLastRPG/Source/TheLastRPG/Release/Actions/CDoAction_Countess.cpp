#include "Release/Actions/CDoAction_Countess.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"

ACDoAction_Countess::ACDoAction_Countess()
{
	Helpers::GetAsset<UParticleSystem>(&HitParticle, "ParticleSystem'/Game/Assets/ParagonCountess/Particles/Abilities/BladeSiphon/FX/p_Countess_BladeSiphon_HitFX.p_Countess_BladeSiphon_HitFX'");
}

void ACDoAction_Countess::DoAction()
{
	Super::DoAction();

}

void ACDoAction_Countess::Begin_DoAction()
{
	Super::Begin_DoAction();

}

void ACDoAction_Countess::End_DoAction()
{
	Super::End_DoAction();
}

void ACDoAction_Countess::DoSkill_Q()
{
	Super::DoSkill_Q();
	CLog::Log("Q\n");

	/// TODO
	/*
		1. 몽타주 재생
		2. State -> Action 설정
		3. Status -> bCanMove 설정
	*/

	CheckFalse(*bEquipped);
	CheckFalse(State->IsIdleMode());
	CheckNull(SkillDatas[(int32)ESkillType::Q].AnimMontage);
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(SkillDatas[(int32)ESkillType::Q].AnimMontage, SkillDatas[(int32)ESkillType::Q].PlayRatio, SkillDatas[(int32)ESkillType::Q].StartSection);
	SkillDatas[(int32)ESkillType::Q].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Countess::Begin_Skill_Q()
{
	Super::Begin_Skill_Q();

	/// TODO
	/*
		1. 충돌체크 SphereTraceMultiForObjects
		2. 충돌처리된 녀석들에게
		- 피격 관련 파티클 재생, TakeDamage, 경직효과 추가
	*/

	Attached = UGameplayStatics::SpawnEmitterAttached(SkillDatas[(int32)ESkillType::Q].Effect, OwnerCharacter->GetMesh(), "");
	Attached->SetRelativeLocation(SkillDatas[(int32)ESkillType::Q].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(SkillDatas[(int32)ESkillType::Q].EffectTransform.GetScale3D());

	FVector start = OwnerCharacter->GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 5.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery6);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	FDamageEvent e;
	CLog::Log("before Trace");
	bool bHitted = false;
	FTransform transform;

	if (UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, CollisionRadius, "Pawn", false, ignoreActors, EDrawDebugTrace::None, hitResults, true))
	{
		for (const FHitResult& hitResult : hitResults)
		{
			ACharacter* character = Cast<ACharacter>(hitResult.Actor);
			CLog::Log(hitResult.GetActor());
			if (!!character)
			{
				// 파티클 재생, TakeDamage, 경직효과
				CLog::Log(character, true);
				bHitted = true;
				character->TakeDamage(SkillDatas[(int32)ESkillType::Q].Power, e, OwnerCharacter->GetController(), this);

				transform.SetLocation(character->GetActorLocation());
				transform += HitEffectOffset;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, transform);
			}
		}
	}

	/// HitStop
	float hitStop = SkillDatas[(int32)ESkillType::Q].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false && bHitted)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1e-3f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStop * 1e-3f, false);
	}

	/// CameraShake
	TSubclassOf<UMatineeCameraShake> shake = SkillDatas[(int32)ESkillType::Q].ShakeClass;
	if (!!shake && bHitted)
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->StartMatineeCameraShake(shake);
}

void ACDoAction_Countess::End_Skill_Q()
{
	Super::End_Skill_Q();

	/// TODO
	/*
		1. State -> Idle 변경
		2. Status -> CanMove 변경
	*/
	State->SetIdleMode();
	Status->SetMove();
	Attached->DestroyComponent();
}

void ACDoAction_Countess::DoSkill_E()
{
	Super::DoSkill_E();
	CLog::Log("E\n");
}

void ACDoAction_Countess::Begin_Skill_E()
{
	Super::Begin_Skill_E();
}

void ACDoAction_Countess::End_Skill_E()
{
	Super::End_Skill_E();
}

void ACDoAction_Countess::DoSkill_R()
{
	Super::DoSkill_R();
	CLog::Log("R\n");
}

void ACDoAction_Countess::Begin_Skill_R()
{
	Super::Begin_Skill_R();
}

void ACDoAction_Countess::End_Skill_R()
{
	Super::End_Skill_R();
}

void ACDoAction_Countess::DoSkill_F()
{
	Super::DoSkill_F();
	CLog::Log("F\n");
}

void ACDoAction_Countess::Begin_Skill_F()
{
	Super::Begin_Skill_F();
}

void ACDoAction_Countess::End_Skill_F()
{
	Super::End_Skill_F();
}

void ACDoAction_Countess::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

}

void ACDoAction_Countess::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);

}

void ACDoAction_Countess::OnAttachmentCollision()
{
	Super::OnAttachmentCollision();
}

void ACDoAction_Countess::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();

}