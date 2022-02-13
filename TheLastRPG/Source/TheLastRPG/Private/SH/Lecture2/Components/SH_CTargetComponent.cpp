#include "SH/Lecture2/Components/SH_CTargetComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

USH_CTargetComponent::USH_CTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SH_CHelpers::GetAsset<UParticleSystem>(&Particle, "ParticleSystem'/Game/Lectures/Effects/P_Enrage_Base.P_Enrage_Base'");
}

void USH_CTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void USH_CTargetComponent::ToggleTarget()
{
	if (!!Target)
	{
		EndTargeting();
		return;
	}

	StartTargeting();
}

void USH_CTargetComponent::StartTargeting()
{
	SetTraceTargets();
	SetTarget();
}

void USH_CTargetComponent::EndTargeting()
{
	Target = NULL;
	TraceTargets.Empty();

	if (!!Attached)
		Attached->DestroyComponent();
}

void USH_CTargetComponent::SetTraceTargets()
{
	FVector start = OwnerCharacter->GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 1);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, TraceRadius, "Pawn", false, ignoreActors, Debug, hitResults, true, FLinearColor::Green, FLinearColor::Red, 1.0f);

	for (const FHitResult& result : hitResults)
	{
		// Ÿ�� ��� ����
		if (result.GetActor()->GetClass() == OwnerCharacter->GetClass())
			continue;
		ACharacter* character = Cast<ACharacter>(result.GetActor());
		if (!!character)
			TraceTargets.AddUnique(character);
	}
}

void USH_CTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckNull(Target); // ������ ����

	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(Target);

	bool b = false;
	b |= state->IsDeadMode();
	b |= Target->GetDistanceTo(OwnerCharacter) >= TraceRadius;

	if (b == true) // Dead || TraceRadius�� ����ų�
	{
		EndTargeting();
		return;
	}

	FVector start = OwnerCharacter->GetActorLocation();
	FVector target = Target->GetActorLocation();

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(start, target);
	FRotator current = OwnerCharacter->GetControlRotation();

	rotator = UKismetMathLibrary::RInterpTo(current, rotator, DeltaTime, InterpSpeed);
	OwnerCharacter->GetController()->SetControlRotation(rotator);
}

void USH_CTargetComponent::SetTarget()
{
	float angle = -2.0f;
	ACharacter* target = NULL;

	for (ACharacter* character : TraceTargets)
	{
		FVector direction = FQuat(OwnerCharacter->GetControlRotation()).GetForwardVector();
		FVector offset = character->GetActorLocation() - OwnerCharacter->GetActorLocation();
		offset = offset.GetSafeNormal();

		float dotProduct = direction | offset; // | : GetDotProductTo, ����
		if (dotProduct < angle)
			continue;

		angle = dotProduct;
		target = character;
	}

	SH_CLog::Print(target->GetActorLabel());
	ChangeCursor(target);
}


void USH_CTargetComponent::ChangeTargetLeft()
{
	ChangeTarget(false);
}

void USH_CTargetComponent::ChangeTargetRight()
{
	ChangeTarget(true);
}

void USH_CTargetComponent::ChangeTarget(bool InRight)
{
	CheckNull(Target);

	/// ���� Ÿ���� �����ϰ� ��� Ÿ�꿡 ���� ����, �������� ���Ѵ�.
	TMap<float, ACharacter*> map;
	for (ACharacter* character : TraceTargets)
	{
		if (Target == character)
			continue;

		FVector targetLocation = character->GetActorLocation();
		FVector ownerLocation = OwnerCharacter->GetActorLocation();
		FVector ownerToTarget = targetLocation - ownerLocation;

		FQuat quat = FQuat(OwnerCharacter->GetControlRotation());
		FVector forward = quat.GetForwardVector();
		FVector up = quat.GetUpVector();

		FVector cross = forward ^ ownerToTarget;
		float dot = cross | up;

		map.Add(dot, character);
	}

	/// ���� ���� �̿��ؼ� �ּҰ��� ���غ���.
	float minimum = FLT_MAX;
	ACharacter* target = NULL;

	TArray<float> keys;
	map.GetKeys(keys);

	for (const float& key : keys)
	{
		if (InRight == true)
		{
			// ������Ű�� �������� ���� �༮���� ����
			if (key < 0.0f)
				continue;
		}
		else
		{
			// ����Ű�� �������� ������ �༮���� ����
			if (key > 0.0f)
				continue;
		}

		if (FMath::Abs(key) > minimum)
			continue;

		minimum = FMath::Abs(key);
		target = *map.Find(key);
	}

	ChangeCursor(target);
}

void USH_CTargetComponent::ChangeCursor(ACharacter* InTarget)
{
	if (!!InTarget)
	{
		if (!!Attached)
			Attached->DestroyComponent();
		Attached = UGameplayStatics::SpawnEmitterAttached(Particle, InTarget->GetMesh(), "Spine_Target");

		Target = InTarget;
		return;
	}

	EndTargeting();
}