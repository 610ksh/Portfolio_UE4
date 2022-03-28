#include "Release/Characters/CCountess.h"
#include "Release/Components/COptionComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Components/CMontageComponent.h"
#include "Release/Global.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACCountess::ACCountess()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	Helpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	Helpers::CreateActorComponent<UCOptionComponent>(this, &Option, "Option");
	Helpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	Helpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	Helpers::CreateActorComponent<UCMontageComponent>(this, &Montages, "Montages");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	bUseControllerRotationYaw = false;

	USkeletalMesh* mesh;
	Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Assets/ParagonCountess/Meshes/SM_Countess.SM_Countess'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	Helpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Projects/Characters/ABP_CCountess.ABP_CCountess_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 150));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACCountess::BeginPlay()
{
	Super::BeginPlay();
	
	State->OnCountessStateTypeChanged.AddDynamic(this, &ACCountess::OnStateTypeChanged);
	//State->SetIdleMode();
}

void ACCountess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCountess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCountess::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCountess::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACCountess::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ACCountess::OnVerticalLook);

	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ACCountess::OnAvoid);
}

void ACCountess::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = GetControlRotation();
	FVector direction = FQuat(rotator).GetForwardVector();
	AddMovementInput(direction, InAxis);
}

void ACCountess::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = GetControlRotation();
	FVector direction = FQuat(rotator).GetRightVector();
	AddMovementInput(direction, InAxis);
}

void ACCountess::OnHorizontalLook(float InAxis)
{
	float turnRate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * turnRate * GetWorld()->GetDeltaSeconds());
}

void ACCountess::OnVerticalLook(float InAxis)
{
	float lookUpRate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * lookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACCountess::OnAvoid()
{
	CheckFalse(Status->CanMove());
	CheckFalse(State->IsIdleMode());

	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackstepMode();
		return;
	}
	State->SetRollMode();
}

void ACCountess::OnStateTypeChanged(ECountessStateType InPrevType, ECountessStateType InNewType)
{
	switch (InNewType)
	{
	case ECountessStateType::Idle:
		break;
	case ECountessStateType::Roll:
		Begin_Roll();
		break;
	case ECountessStateType::Backstep:
		Begin_Backstep();
		break;
	default:
		break;
	}
}

void ACCountess::Begin_Roll()
{

	End_Roll();
}

void ACCountess::End_Roll()
{
	CLog::Log(L"End_Roll");
}

void ACCountess::Begin_Backstep()
{

	End_Backstep();
}

void ACCountess::End_Backstep()
{
	CLog::Log(L"End_Backstep");
}