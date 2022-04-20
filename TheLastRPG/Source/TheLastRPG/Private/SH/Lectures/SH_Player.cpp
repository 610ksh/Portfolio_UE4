#include "SH/Lectures/SH_Player.h"
#include "SH/Lectures/SH_CAnimInstance.h"
#include "SH/Lectures/SH_CRifle.h"
#include "SH/Lectures/Widgets/SH_CUserWidget_CrossHair.h"
#include "SH/SH_Global.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ASH_Player::ASH_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	SH_CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동하는 방향으로 회전가능
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
	SpringArm->bDoCollisionTest = false; // 카메라와 물체 사이의 충돌체크 하겠냐는것. 카메라가 뒤집어질 수 있음. 끔.
	SpringArm->bUsePawnControlRotation = true; // 컨트롤러에 따라 폰이 움직여야 하기 떄문에 켜준다.
	SpringArm->SocketOffset = FVector(0, 60, 0); // 앞의 선을 살짝 올려둠.

	SH_CHelpers::GetClass<USH_CUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/SungHoon/Lectures/GunShooting/Widgets/SH_WB_CrossHair.SH_WB_CrossHair_C'");
	SH_CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/SungHoon/Lectures/GunShooting/Blueprints/SH_BP_CameraShake.SH_BP_CameraShake_C'");
}

void ASH_Player::GetLocationAndDirection(FVector & OutStart, FVector & OutEnd, FVector & OutDirection)
{
	OutDirection = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector cameraLocation = transform.GetLocation();
	OutStart = cameraLocation + OutDirection; // 카메라 위치보다 좀더 앞의 방향

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
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	CrossHair = CreateWidget<USH_CUserWidget_CrossHair, APlayerController>(GetController<APlayerController>(), CrossHairClass);
	CrossHair->AddToViewport();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);

	Rifle = ASH_CRifle::Spawn(GetWorld(), this);
	OnRifle();
}

void ASH_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/// Movement(이동과 회전)
	PlayerInputComponent->BindAxis("MoveForward", this, &ASH_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASH_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASH_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &ASH_Player::OnVerticalLook);

	/// Running(Shift), Rifle(총 장착&해제)
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ASH_Player::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ASH_Player::OffRunning);
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Released, this, &ASH_Player::OnRifle);

	/// Aim
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ASH_Player::OnAim); // 누르면
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ASH_Player::OffAim); // 떼면

	/// Fire
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASH_Player::OnFire); // 누르면
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ASH_Player::OffFire); // 떼면
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
	GetController<APlayerController>()->PlayerCameraManager->StartMatineeCameraShake(CameraShakeClass);
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
	// 좌우 카메라 회전
	AddControllerYawInput(Axis);
}

void ASH_Player::OnVerticalLook(float Axis)
{
	// 위아래 카메라 회전
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
	SH_CheckFalse(Rifle->GetEquipped());
	SH_CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->TargetArmLength = 100; // 길이 당김
	SpringArm->SocketOffset = FVector(0, 30, 10); // 소켓 위치 변경
	
	//Camera->FieldOfView = 40; // 시야 좁힘. Curve가 해줄거임
	OnZoomIn(); // BP에서 이벤트 노드로 재정의함
	Rifle->Begin_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Visible);
}

void ASH_Player::OffAim()
{
	SH_CheckFalse(Rifle->GetEquipped());
	SH_CheckTrue(Rifle->GetEquipping());

	/// 전부 기본으로 돌림. 초기값 셋팅으로.
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	//Camera->FieldOfView = 90; // 원상 복구. Curve가 해줄거임
	OnZoomOut(); // BP에서 이벤트 노드로 재정의함
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
