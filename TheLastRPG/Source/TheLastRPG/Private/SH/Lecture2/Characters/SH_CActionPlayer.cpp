#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Components/SH_COptionActorComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/SH_Global.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASH_CActionPlayer::ASH_CActionPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	SH_CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SH_CHelpers::CreateActorComponent<USH_CActionComponent>(this, &Action, "Action");
	SH_CHelpers::CreateActorComponent<USH_CMontagesComponent>(this, &Montages, "Montages");
	SH_CHelpers::CreateActorComponent<USH_COptionActorComponent>(this, &Option, "Option");
	SH_CHelpers::CreateActorComponent<USH_CStatusComponent>(this, &Status, "Status");
	SH_CHelpers::CreateActorComponent<USH_CStateComponent>(this, &State, "State");

	bUseControllerRotationYaw = false;
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SungHoon/Lectures/ActionRPG/Character/Mesh/SH_Mannequin.SH_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	SH_CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Lectures/ActionRPG/Character/SH_ABP_CPlayer.SH_ABP_CPlayer_C'"); // _C
	GetMesh()->SetAnimClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 180));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0)); // 좌우 회전으로 90도 = Yaw
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true; // ?
	SpringArm->bEnableCameraLag = true; //?

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ASH_CActionPlayer::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ASH_CActionPlayer::OnStateTypeChanged);
}

void ASH_CActionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASH_CActionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASH_CActionPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASH_CActionPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASH_CActionPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ASH_CActionPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnAvoid);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnOneHand);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnDoAction);
}

void ASH_CActionPlayer::OnMoveForward(float Axis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ASH_CActionPlayer::OnMoveRight(float Axis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ASH_CActionPlayer::OnHorizontalLook(float Axis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(Axis * rate * GetWorld()->GetDeltaSeconds());
}

void ASH_CActionPlayer::OnVerticalLook(float Axis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(Axis * rate * GetWorld()->GetDeltaSeconds());
}

void ASH_CActionPlayer::OnAvoid()
{
	CheckFalse(Status->CanMove()); // 움직일수 없으면 return
	CheckFalse(State->IsIdleMode()); // Idle 모드가 아니라면 return

	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackstepMode(); // 뒤로가는 버튼을 눌렀다면
		return;
	}
	State->SetRollMode(); // 뒤로가는거 아니면 Roll
}


void ASH_CActionPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Roll:
		Begin_Roll();
		break;
	case EStateType::Backstep:
		Begin_Backstep();
		break;
	}
}

void ASH_CActionPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false; // 구르는 도중에 좌우 회전은 막음
	GetCharacterMovement()->bOrientRotationToMovement = true; // 현재 이동하려고 하는 방향으로 움직이도록함

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D(); // 현재 카메라 바라보는방향 벡터
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from)); // 현재 위치에서 바라보는 방향으로 회전

	Montages->PlayRoll();
}

void ASH_CActionPlayer::End_Roll()
{
	if (Action->IsUnarmedMode() == false) // 무기를 들고 있다면
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
}

void ASH_CActionPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true; // 뒤로가면서 좌우 회전가능
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
}

void ASH_CActionPlayer::End_Backstep()
{
	if (Action->IsUnarmedMode()) // 무기일땐 풀어주면 안됨.
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	State->SetIdleMode();
}

void ASH_CActionPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandMode();
}

void ASH_CActionPlayer::OnDoAction()
{
	Action->DoAction();
}