#include "SH/Lectures/SH_Player.h"
#include "SH/Lectures/SH_CAnimInstance.h"
#include "SH/Lectures/SH_CRifle.h"
#include "SH/Lectures/Widgets/SH_CUserWidget_CrossHair.h"
#include "SH/SH_Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "Components/CapsuleComponent.h" // for GetCapsuleComponent
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ASH_Player::ASH_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetCapsuleComponent());

	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(SpringArm);

	SH_CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	SH_CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // �̵��ϴ� �������� ȸ������
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	USkeletalMesh* mesh;
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SungHoon/Lectures/GunShooting/Character/SH_Female.SH_Female'");
	GetMesh()->SetSkeletalMesh(mesh);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	SH_CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Lectures/GunShooting/Character/SH_ABP_CPlayer.SH_ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false; // ī�޶�� ��ü ������ �浹üũ �ϰڳĴ°�. ī�޶� �������� �� ����. ��.
	SpringArm->bUsePawnControlRotation = true; // ��Ʈ�ѷ��� ���� ���� �������� �ϱ� ������ ���ش�.
	SpringArm->SocketOffset = FVector(0, 60, 0); // ���� ���� ��¦ �÷���.

	SH_CHelpers::GetClass<USH_CUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/SungHoon/Lectures/GunShooting/Widgets/SH_WB_CrossHair.SH_WB_CrossHair_C'");
	SH_CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/SungHoon/Lectures/GunShooting/Blueprints/SH_BP_CameraShake.SH_BP_CameraShake_C'");
}

void ASH_Player::GetLocationAndDirection(FVector & OutStart, FVector & OutEnd, FVector & OutDirection)
{
	OutDirection = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector cameraLocation = transform.GetLocation();
	OutStart = cameraLocation + OutDirection; // ī�޶� ��ġ���� ���� ���� ����

	FVector conDirection = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(OutDirection, 0.2f, 0.3f);
	conDirection *= 3000.0f;

	OutEnd = cameraLocation + conDirection;
}

void ASH_Player::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* bodyMaterial;
	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&bodyMaterial, "MaterialInstanceConstant'/Game/SungHoon/Lectures/GunShooting/Character/SH_MI_Female_Body_Inst.SH_MI_Female_Body_Inst'");

	UMaterialInstanceConstant* logoMaterial;
	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterial, "MaterialInstanceConstant'/Game/SungHoon/Lectures/GunShooting/Character/SH_M_Female_ChestLogo_Inst.SH_M_Female_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial, this);
	GetMesh()->SetMaterial(0, BodyMaterial); // 0��° �ε����� �츮�� ���� ��Ƽ������ �Ҵ��Ѵ�.
	GetMesh()->SetMaterial(1, LogoMaterial); // 1��° �ε����� �츮�� ���� ��Ƽ������ �Ҵ��Ѵ�.

	CrossHair = CreateWidget<USH_CUserWidget_CrossHair, APlayerController>(GetController<APlayerController>(), CrossHairClass);
	CrossHair->AddToViewport();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);

	Rifle = ASH_CRifle::Spawn(GetWorld(), this);
	OnRifle(); // �������ڸ��� ���� �����ϵ��� �Լ� ����
}

void ASH_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/// Movement(�̵��� ȸ��)
	PlayerInputComponent->BindAxis("MoveForward", this, &ASH_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASH_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASH_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ASH_Player::OnVerticalLook);

	/// Running(Shift), Rifle(�� ����&����)
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ASH_Player::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ASH_Player::OffRunning);
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Released, this, &ASH_Player::OnRifle);

	/// Aim
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ASH_Player::OnAim); // ������
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ASH_Player::OffAim); // ����

	/// Fire
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASH_Player::OnFire); // ������
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ASH_Player::OffFire); // ����
}

void ASH_Player::OnFocus()
{
	CrossHair->OnFocus();
}

void ASH_Player::OffFocus()
{
	CrossHair->OffFocus();
}

void ASH_Player::PlayCameraShake()
{
	GetController<APlayerController>()->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}

void ASH_Player::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();
	
	AddMovementInput(direction, Axis);
}

void ASH_Player::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ASH_Player::OnHorizontalLook(float Axis)
{
	// �¿� ī�޶� ȸ��
	AddControllerYawInput(Axis);
}

void ASH_Player::OnVerticalLook(float Axis)
{
	// ���Ʒ� ī�޶� ȸ��
	AddControllerPitchInput(Axis);
}

void ASH_Player::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200;
	SH_CLog::Log(FString::Printf(TEXT("Success OnRunning! MaxWalkSpeed : %f"), GetCharacterMovement()->MaxWalkSpeed));
}

void ASH_Player::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 500;
	SH_CLog::Log(FString::Printf(TEXT("Success OffRunning! MaxWalkSpeed : %f"), GetCharacterMovement()->MaxWalkSpeed));
}

void ASH_Player::OnRifle()
{
	SH_CLog::Log(FString("Success OnRifle!"));

	if (Rifle->GetEquipped())
	{
		Rifle->Unequip();
		SH_CLog::Log(FString("Unequip!"));
		return;
	}
	Rifle->Equip();
	SH_CLog::Log(FString(L"Equip!"));
}

void ASH_Player::OnAim()
{
	CheckFalse(Rifle->GetEquipped()); // �������� ������
	CheckTrue(Rifle->GetEquipping()); // ��� �ִ� �����̾ pass

	bUseControllerRotationYaw = true; // ���ظ�尡 ���۵Ǹ�, ī�޶��� �������� ��.
	GetCharacterMovement()->bOrientRotationToMovement = false; // �̵��������� ȸ���ϴ°� ����

	SpringArm->TargetArmLength = 100; // ���� ���
	SpringArm->SocketOffset = FVector(0, 30, 10); // ���� ��ġ ����
	
	//Camera->FieldOfView = 40; // �þ� ����. Curve�� ���ٰ���
	OnZoomIn(); // BP���� �̺�Ʈ ���� ��������
	Rifle->Begin_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Visible);
}

void ASH_Player::OffAim()
{
	CheckFalse(Rifle->GetEquipped()); // �������� ������
	CheckTrue(Rifle->GetEquipping()); // ��� �ִ� �����̾ pass

	/// ���� �⺻���� ����. �ʱⰪ ��������.
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	//Camera->FieldOfView = 90; // ���� ����. Curve�� ���ٰ���
	OnZoomOut(); // BP���� �̺�Ʈ ���� ��������
	Rifle->End_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);
}

void ASH_Player::OnFire()
{
	Rifle->Begin_Fire();
}

void ASH_Player::OffFire()
{
	Rifle->End_Fire();
}

void ASH_Player::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}
