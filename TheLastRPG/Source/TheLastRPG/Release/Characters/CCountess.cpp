#include "Release/Characters/CCountess.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Components/COptionComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Components/CMontageComponent.h"
#include "Release/Global.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACCountess::ACCountess()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	Helpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	Helpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");
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

	SpringArm->SetRelativeLocation(FVector(0, 0, 200));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 250.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bUsePawnControlRotation = true;
	
	Camera->SetRelativeRotation(FRotator(-10, 0, 0));

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACCountess::BeginPlay()
{
	Super::BeginPlay();

	State->OnCountessStateTypeChanged.AddDynamic(this, &ACCountess::OnStateTypeChanged);

	UMaterialInstanceConstant* top;
	UMaterialInstanceConstant* bottom;

	Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&bottom, "MaterialInstanceConstant'/Game/SungHoon/Projects/Characters/Materials/M_Countess_Bottom_Inst.M_Countess_Bottom_Inst'");
	Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&top, "MaterialInstanceConstant'/Game/SungHoon/Projects/Characters/Materials/M_Countess_Top_Inst.M_Countess_Top_Inst'");

	BottomMaterial = UMaterialInstanceDynamic::Create(bottom, this);
	TopMaterial = UMaterialInstanceDynamic::Create(top, this);

	GetMesh()->SetMaterial(1, BottomMaterial);
	GetMesh()->SetMaterial(2, TopMaterial);

	Action->SetUnarmedMode();
}

#pragma region Delegate
/// DeleGate

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
#pragma endregion

void ACCountess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region InputComponent
/// InputComponent, Bind function

void ACCountess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCountess::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCountess::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACCountess::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ACCountess::OnVerticalLook);

	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ACCountess::OnAvoid);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ACCountess::OnOneHand);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACCountess::OnDoAction);
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
#pragma endregion

#pragma region Movement
/// Movement, Roll, Backstep

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

void ACCountess::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from));

	Montages->PlayRoll();
}

void ACCountess::End_Roll()
{
	if (Action->IsUnarmedMode() == false)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
	CLog::Log(L"End_Roll");
}

void ACCountess::Begin_Backstep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
}

void ACCountess::End_Backstep()
{
	if (Action->IsUnarmedMode())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	State->SetIdleMode();
	CLog::Log(L"End_Backstep");
}
#pragma endregion

#pragma region Equipment
/// Equip State

void ACCountess::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandMode();
}
#pragma endregion

#pragma region Attack
/// Attack

void ACCountess::OnDoAction()
{
	Action->DoAction();
}
#pragma endregion

void ACCountess::ChangeColor(FLinearColor InColor)
{
	TopMaterial->SetVectorParameterValue("LatexColor", InColor);
	BottomMaterial->SetVectorParameterValue("LatexColor", InColor);
}