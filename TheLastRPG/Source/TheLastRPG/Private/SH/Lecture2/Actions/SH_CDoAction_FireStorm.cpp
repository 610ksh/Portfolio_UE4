#include "SH/Lecture2/Actions/SH_CDoAction_FireStorm.h"
#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

void ASH_CDoAction_FireStorm::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		// Owner가 갖고 있는 자식 컴포넌트들을 모조리 가져옴.
		if (actor->IsA<ASH_CAttachment>() && actor->GetActorLabel().Contains("FireStorm"))
		{
			Box = SH_CHelpers::GetComponent<UBoxComponent>(actor); // actor에서 Box찾아옴
			break;
		}
	}
}

void ASH_CDoAction_FireStorm::DoAction()
{
	SH_CheckFalse(*bEquipped);
	SH_CheckFalse(State->IsIdleMode());

	State->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_FireStorm::Begin_DoAction()
{
	Angle = UKismetMathLibrary::RandomFloatInRange(0, 360);

	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ASH_CAttachment* attachment = Cast<ASH_CAttachment>(Box->GetOwner());
	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ASH_CDoAction_FireStorm::End_DoActin()
{
	Status->SetMove();

	FTimerDynamicDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "Finish");

	UKismetSystemLibrary::K2_SetTimerDelegate(timerDelegate, Time, false);
}

void ASH_CDoAction_FireStorm::Finish()
{
	State->SetIdleMode();
	Attached->DestroyComponent();

	ASH_CAttachment* attachment = Cast<ASH_CAttachment>(Box->GetOwner());
	attachment->OffCollision();

	UKismetSystemLibrary::K2_ClearTimer(this,"Hitted");
}

void ASH_CDoAction_FireStorm::Hitted()
{
	FDamageEvent e;
	for (ACharacter* character : HittedCharacter)
		character->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
}

void ASH_CDoAction_FireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SH_CheckFalse(*bEquipped);
	SH_CheckFalse(State->IsActionMode());

	FVector location = OwnerCharacter->GetActorLocation();

	Angle += Speed * DeltaTime;
	if (FMath::IsNearlyEqual(Angle, 360))
		Angle = 0.0f;

	FVector axis = FVector(Distance, 0, 0);
	FVector value = axis.RotateAngleAxis(Angle, FVector(0, 0, 1));
	location += value;
	
	Box->SetWorldLocation(location);
}

void ASH_CDoAction_FireStorm::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	HittedCharacter.AddUnique(InOtherCharacter);
}

void ASH_CDoAction_FireStorm::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	HittedCharacter.Remove(InOtherCharacter);
}