#include "SH/Lecture2/Actions/SH_CDoAction_Warp.h"
#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"

#include "SH/SH_Global.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"

void ASH_CDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ASH_CAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = SH_CHelpers::GetComponent<UDecalComponent>(actor);
			break;
		}
	}
}

void ASH_CDoAction_Warp::DoAction()
{
	SH_CheckFalse(*bEquipped);
	SH_CheckFalse(State->IsIdleMode());

	if (UseCursorLocation()) // Player
	{
		FRotator rotator;
		SH_CheckFalse(GetCursorLocationAndRotation(Location, rotator));
	}
	else // AI
	{
		ASH_CAIController* controller = OwnerCharacter->GetController<ASH_CAIController>();
		USH_CBehaviorComponent* behavior = SH_CHelpers::GetComponent<USH_CBehaviorComponent>(controller);
		
		Location = behavior->GetWarpLocation();
		Decal->SetVisibility(false);
	}

	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_Warp::Begin_DoAction()
{
	FTransform transform = Datas[0].EffectTransform;
	//transform.AddToTranslation(OwnerCharacter->GetActorLocation());
	UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, OwnerCharacter->GetMesh(), "", transform.GetLocation(), FRotator(transform.GetRotation()), transform.GetScale3D());
}

void ASH_CDoAction_Warp::End_DoActin()
{
	OwnerCharacter->SetActorLocation(Location);
	Location = FVector::ZeroVector; // ÃÊ±âÈ­

	State->SetIdleMode();
	Status->SetMove();
}

void ASH_CDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SH_CheckFalse(*bEquipped);

	if (UseCursorLocation() == false)
	{
		Decal->SetVisibility(false);
		return;
	}

	FVector location;
	FRotator rotator;
	if (GetCursorLocationAndRotation(location, rotator))
	{
		Decal->SetVisibility(true);
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotator);
		return;
	}
	else
		Decal->SetVisibility(false);
}

bool ASH_CDoAction_Warp::UseCursorLocation()
{
	return OwnerCharacter->GetController<ASH_CAIController>() == NULL;
}

bool ASH_CDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator)
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