#include "SH/Lecture2/Actions/SH_CAim.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/SH_CHUD.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

USH_CAim::USH_CAim()
{
	SH_CHelpers::GetAssetDynamic<UCurveFloat>(&Curve, "CurveFloat'/Game/SungHoon/Lectures/ActionRPG/Data/SH_C_Aim.SH_C_Aim'");
}

void USH_CAim::BeginPlay(ACharacter * InCharacter)
{
	OwnerCharacter = InCharacter;

	SpringArm = SH_CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = SH_CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = SH_CHelpers::GetComponent<USH_CStateComponent>(OwnerCharacter);

	HUD = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ASH_CHUD>();

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200);
}

void USH_CAim::OnZoom()
{
	SH_CheckFalse(IsAvailable()); // 이용할 수 있다면
	SH_CheckTrue(bInZoom); // 줌 중이면 종료
	SH_CLog::Print("OnAim");

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0,30,10);
	SpringArm->bEnableCameraLag = false;

	//Camera->FieldOfView = 45;
	Timeline.PlayFromStart();
	HUD->SetDrawMode();
}

void USH_CAim::OffZoom()
{
	SH_CheckFalse(bInZoom); // 줌이 아니라면 종료
	SH_CLog::Print("OffAim");

	// 원상 복구
	bInZoom = false;

	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	HUD->SetUndrawMode();

	//Camera->FieldOfView = 90;
	Timeline.ReverseFromEnd();
}

void USH_CAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void USH_CAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}