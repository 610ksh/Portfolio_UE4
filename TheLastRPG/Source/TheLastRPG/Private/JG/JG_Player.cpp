

#include "JG/JG_Player.h"
#include "JG/JG_Global.h"
#include "JG/JG_Rifle.h"
#include "JG/JG_AnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


AJG_Player::AJG_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetCapsuleComponent());

	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(SpringArm);

	JG_Helpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	JG_Helpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	// �����ڿ����Ƿ� ����
	USkeletalMesh* mesh;
	JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/JongGyun/Character/JG_Mannequin.JG_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	JG_Helpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/JongGyun/Character/ABP_JG_Anim.ABP_JG_Anim_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60,0);

}

// Called when the game starts or when spawned
void AJG_Player::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* bodyMaterial;
	JG_Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&bodyMaterial, "MaterialInstanceConstant'/Game/JongGyun/Materials/M_Male_Body_Inst.M_Male_Body_Inst'");

	UMaterialInstanceConstant* logoMaterial;
	JG_Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterial, "MaterialInstanceConstant'/Game/JongGyun/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial, this);
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Rifle = AJG_Rifle::Spawn(GetWorld(), this);

	OnRifle();
}

// Called every frame
void AJG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJG_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJG_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJG_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AJG_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &AJG_Player::OnVerticalLook);

	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &AJG_Player::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &AJG_Player::OffRunning);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &AJG_Player::OnRifle);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &AJG_Player::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &AJG_Player::OffAim);

}

void AJG_Player::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AJG_Player::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AJG_Player::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}
void AJG_Player::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);

}

void AJG_Player::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AJG_Player::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 200;
}

void AJG_Player::OnRifle()
{
	if (Rifle->GetEquipped())
	{
		Rifle->Unequip();

		// if-else���� return�� �������� ���� �������� ����
		return;
	}

	Rifle->Equip();
}

void AJG_Player::OnAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	Camera->FieldOfView = 40;

}

void AJG_Player::OffAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	Camera->FieldOfView = 90;
}


void AJG_Player::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}
