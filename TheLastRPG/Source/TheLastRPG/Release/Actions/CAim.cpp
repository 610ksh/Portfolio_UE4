#include "Release/Actions/CAim.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

UCAim::UCAim()
{
	Helpers::GetAssetDynamic<UCurveFloat>(&Curve, "CurveFloat'/Game/SungHoon/Projects/Actions/C_Aim.C_Aim'");
}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArm = Helpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = Helpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = Helpers::GetComponent<UCStateComponent>(OwnerCharacter);

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200.f);
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::OnZoom()
{
	CheckFalse(IsAvailable());
	CheckTrue(bInZoom);
	CLog::Log("OnAim");

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	//Camera->FieldOfView = 45.f;
	Timeline.PlayFromStart();
}

void UCAim::OffZoom()
{
	CheckFalse(bInZoom);
	CLog::Log("OffAim");

	bInZoom = false;

	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = false;

	//Camera->FieldOfView = 90.f;
	Timeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	CLog::Print(Output, 0);
	Camera->FieldOfView = Output;
}