#include "SH/Lecture2/Characters/SH_CActionPlayer2.h"
#include "SH/Lecture2/SH_CACtionAnimInstance.h"
#include "SH/Lecture2/Components/SH_COptionActorComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

ASH_CActionPlayer2::ASH_CActionPlayer2()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	SH_CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SH_CHelpers::CreateActorComponent<USH_COptionActorComponent>(this, &Option, "Option");

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

	SH_CHelpers::GetAsset<UAnimMontage>(&Montage, "AnimMontage'/Game/SungHoon/Lectures/ActionRPG/Character/Montages/Common/SH_Roll_Montage.SH_Roll_Montage'");
}

void ASH_CActionPlayer2::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASH_CActionPlayer2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASH_CActionPlayer2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASH_CActionPlayer2::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASH_CActionPlayer2::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASH_CActionPlayer2::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ASH_CActionPlayer2::OnVerticalLook);

	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer2::Dodge);
}


void ASH_CActionPlayer2::OnMoveForward(float Axis)
{
	//CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ASH_CActionPlayer2::OnMoveRight(float Axis)
{
	//CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ASH_CActionPlayer2::OnHorizontalLook(float Axis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(Axis * rate * GetWorld()->GetDeltaSeconds());
}

void ASH_CActionPlayer2::OnVerticalLook(float Axis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(Axis * rate * GetWorld()->GetDeltaSeconds());
}

void ASH_CActionPlayer2::Dodge()
{
	SH_CLog::Print("Dodge");
	CheckNull(Montage);
	PlayAnimMontage(Montage);
}