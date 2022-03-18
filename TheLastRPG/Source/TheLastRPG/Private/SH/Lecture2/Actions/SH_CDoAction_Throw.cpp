#include "SH/Lecture2/Actions/SH_CDoAction_Throw.h"
#include "SH/Lecture2/Actions/SH_CAim.h"
#include "SH/Lecture2/Actions/SH_CThrow.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"

void ASH_CDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<USH_CAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ASH_CDoAction_Throw::DoAction()
{
	if (Aim->IsAvailable())
		CheckFalse_SH(Aim->IsZoom()); // 줌을 하고 있을때만

	CheckFalse_SH(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_Throw::Begin_DoAction()
{
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Throw_Projectile");
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotator));

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;

	ASH_CThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CThrow>(Datas[0].ThrowClass, transform, OwnerCharacter,NULL,ESpawnActorCollisionHandlingMethod::AlwaysSpawn); // 반드시 뒤늦게라도 생성
	//ASH_CThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActor<ASH_CThrow>(Datas[0].ThrowClass, transform, params);
	throwObject->OnThrowBeginOverlap.AddDynamic(this, &ASH_CDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(throwObject, transform);
}

void ASH_CDoAction_Throw::End_DoActin()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ASH_CDoAction_Throw::OnAim()
{
	Aim->OnZoom();
}

void ASH_CDoAction_Throw::OffAim()
{
	Aim->OffZoom();
}

void ASH_CDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ASH_CDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent e;
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
}