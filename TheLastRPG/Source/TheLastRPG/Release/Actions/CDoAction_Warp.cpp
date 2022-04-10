#include "Release/Actions/CDoAction_Warp.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = Helpers::GetComponent<UDecalComponent>(actor);
			CLog::Log(actor->GetName(), true);
			break;
		}
	}

}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckFalse(*bEquipped);

	FVector location;
	FRotator rotator;
	if (GetCursorLocationAndRotation(location, rotator))
	{
		Decal->SetVisibility(true);
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotator);
		return;
	}
	Decal->SetVisibility(false);

}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector & OutLocation, FRotator & OutRotator)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotator = hitResult.ImpactNormal.Rotation();
		return true;
	}

	return false;
}

void ACDoAction_Warp::DoAction()
{
	CheckFalse(*bEquipped);

	FRotator rotator;
	CheckFalse(GetCursorLocationAndRotation(Location, rotator));

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	Decal->SetWorldLocation(Location);
	Decal->SetWorldRotation(rotator);

	OwnerCharacter->PlayAnimMontage(AttackDatas[0].AnimMontage, AttackDatas[0].PlayRatio, AttackDatas[0].StartSection);
	AttackDatas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Warp::Begin_DoAction()
{
	FTransform transform = AttackDatas[0].EffectTransform;
	UGameplayStatics::SpawnEmitterAttached(AttackDatas[0].Effect, OwnerCharacter->GetMesh(), "", transform.GetLocation(), FRotator(transform.GetRotation()), transform.GetScale3D());
}

void ACDoAction_Warp::End_DoAction()
{
	OwnerCharacter->SetActorLocation(Location);
	Location = FVector::ZeroVector;

	State->SetIdleMode();
	Status->SetMove();
}

