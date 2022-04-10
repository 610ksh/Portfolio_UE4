#include "Release/Actions/CDoAction_FireStorm.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

void ACDoAction_FireStorm::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("FireStorm"))
		{
			Box = Helpers::GetComponent<UBoxComponent>(actor);
			break;
		}
	}
}

void ACDoAction_FireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(*bEquipped);
	CheckFalse(State->IsActionMode());

	FVector location = OwnerCharacter->GetActorLocation();
	Angle += Speed * DeltaTime;
	
	if (FMath::IsNearlyEqual(Angle, 360))
		Angle = 0.0f;
	
	FVector axis = FVector(Distance, 0, 0);
	FVector value = axis.RotateAngleAxis(Angle, FVector(0, 0, 1));
	location += value;

	Box->SetWorldLocation(location);
}

void ACDoAction_FireStorm::OnAttachmentBeginOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	HittedCharacter.Emplace(InOtherCharacter);
}

void ACDoAction_FireStorm::OnAttachmentEndOverlap(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOtherCharacter)
{
	HittedCharacter.Remove(InOtherCharacter);
}

void ACDoAction_FireStorm::DoAction()
{
	CheckFalse(*bEquipped);

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(AttackDatas[0].AnimMontage, AttackDatas[0].PlayRatio, AttackDatas[0].StartSection);
	AttackDatas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_FireStorm::Begin_DoAction()
{
	Angle = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);

	Attached = UGameplayStatics::SpawnEmitterAttached(AttackDatas[0].Effect, Box, "");
	Attached->SetRelativeLocation(AttackDatas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(AttackDatas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ACDoAction_FireStorm::Hitted()
{
	FDamageEvent e;
	for (ACharacter* character : HittedCharacter)
		character->TakeDamage(AttackDatas[0].Power, e, OwnerCharacter->GetController(), this);
}

void ACDoAction_FireStorm::End_DoAction()
{
	Status->SetMove();

	FTimerDynamicDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timerDelegate, Time, false);
}

void ACDoAction_FireStorm::Finish()
{
	State->SetIdleMode();
	Attached->DestroyComponent();

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OffCollision();
	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}