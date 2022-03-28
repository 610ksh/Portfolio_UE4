#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Components/SH_CTargetComponent.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Components/SH_COptionActorComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/Lecture2/Components/SH_CFeetComponent.h"
#include "SH/Lecture2/Widgets/SH_CUserWidget_ActionList.h"
#include "SH/SH_Global.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ASH_CActionPlayer::ASH_CActionPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	SH_CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SH_CHelpers::CreateActorComponent<USH_CActionComponent>(this, &Action, "Action");
	SH_CHelpers::CreateActorComponent<USH_CTargetComponent>(this, &Target, "Target");
	SH_CHelpers::CreateActorComponent<USH_CMontagesComponent>(this, &Montages, "Montages");
	SH_CHelpers::CreateActorComponent<USH_CFeetComponent>(this, &Feet, "Feet");
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
	SH_CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Lectures/ActionRPG/Character/SH_ABP_CActionPlayer.SH_ABP_CActionPlayer_C'"); // _C
	GetMesh()->SetAnimClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 180));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0)); // �¿� ȸ������ 90�� = Yaw
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true; // ?
	SpringArm->bEnableCameraLag = true; //?

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;


	SH_CHelpers::GetClass<USH_CUserWidget_ActionList>(&ActionListClass, "WidgetBlueprint'/Game/SungHoon/Lectures/ActionRPG/Widgets/SH_WB_ActionList.SH_WB_ActionList_C'"); // _C
}

void ASH_CActionPlayer::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ASH_CActionPlayer::OnStateTypeChanged);

	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;

	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/SungHoon/Lectures/ActionRPG/Character/Materials/SH_Action_Body_Inst.SH_Action_Body_Inst'");
	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/SungHoon/Lectures/ActionRPG/Character/Materials/SH_Action_ChestLogo_Inst.SH_Action_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Action->SetUnarmedMode(); // �������� UnarmedMode�� ����

	ActionList = CreateWidget<USH_CUserWidget_ActionList, APlayerController>(GetController<APlayerController>(), ActionListClass);
	ActionList->AddToViewport();
	ActionList->SetVisibility(ESlateVisibility::Hidden);

	ActionList->GetData(0).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnFist);
	ActionList->GetData(1).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnOneHand);
	ActionList->GetData(2).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnTwoHand);
	ActionList->GetData(3).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnWarp);
	ActionList->GetData(4).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnFireStorm);
	ActionList->GetData(5).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ASH_CActionPlayer::OnIceBall);
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
	PlayerInputComponent->BindAxis("Zoom", this, &ASH_CActionPlayer::OnZoom);

	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnAvoid); // space

	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnFist); // 1
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnOneHand); // 2
	PlayerInputComponent->BindAction("TwoHand", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnTwoHand); // 3
	PlayerInputComponent->BindAction("Warp", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnWarp); // F
	PlayerInputComponent->BindAction("FireStorm", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnFireStorm); // F
	PlayerInputComponent->BindAction("IceBall", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnIceBall); // F

	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnDoAction); // left mouse

	PlayerInputComponent->BindAction("Target", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnTarget); // Tab
	PlayerInputComponent->BindAction("TargetLeft", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnTargetLeft); // Tab
	PlayerInputComponent->BindAction("TargetRight", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnTargetRight); // Tab

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnAim); // right mouse
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ASH_CActionPlayer::OffAim); // right mouse

	PlayerInputComponent->BindAction("ViewActionList", EInputEvent::IE_Pressed, this, &ASH_CActionPlayer::OnViewActionList); // left Ctrl
	PlayerInputComponent->BindAction("ViewActionList", EInputEvent::IE_Released, this, &ASH_CActionPlayer::OffViewActionList); // left Ctrl
}

FGenericTeamId ASH_CActionPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
}

void ASH_CActionPlayer::OnMoveForward(float Axis)
{
	CheckFalse_SH(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ASH_CActionPlayer::OnMoveRight(float Axis)
{
	CheckFalse_SH(Status->CanMove());

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

void ASH_CActionPlayer::OnZoom(float Axis)
{
	SpringArm->TargetArmLength += (2000.0f * Axis * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 50.0f, 500.0f);
}

void ASH_CActionPlayer::OnAvoid()
{
	CheckFalse_SH(Status->CanMove()); // �����ϼ� ������ return
	CheckFalse_SH(State->IsIdleMode()); // Idle ��尡 �ƴ϶�� return

	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackstepMode(); // �ڷΰ��� ��ư�� �����ٸ�
		return;
	}
	State->SetRollMode(); // �ڷΰ��°� �ƴϸ� Roll
}

void ASH_CActionPlayer::OnStateTypeChanged(SH_EStateType InPrevType, SH_EStateType InNewType)
{
	switch (InNewType)
	{
	case SH_EStateType::Roll:
		Begin_Roll();
		break;
	case SH_EStateType::Backstep:
		Begin_Backstep();
		break;
	case SH_EStateType::Hitted:
		Hitted();
		break;
	case SH_EStateType::Dead:
		Dead();
		break;
	}
}

float ASH_CActionPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageInstigator = EventInstigator; // Ÿ���� �� ��� = Player
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	SH_CLog::Log(Damage);

	State->SetHittedMode();

	return Status->GetHealth();
}

void ASH_CActionPlayer::Hitted()
{
	Status->SubHealth(DamageValue);
	DamageValue = 0.0f;

	/// Dead
	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	Montages->PlayHitted();
}

void ASH_CActionPlayer::Dead()
{
	CheckFalse_SH(State->IsDeadMode());
	Montages->PlayDead();
}

void ASH_CActionPlayer::Begin_Dead()
{
	Action->OffAllCollision();
	Action->DestroyAllActions();
}

void ASH_CActionPlayer::End_Dead()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetController<APlayerController>(), EQuitPreference::Quit, false);
}

void ASH_CActionPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false; // ������ ���߿� �¿� ȸ���� ����
	GetCharacterMovement()->bOrientRotationToMovement = true; // ���� �̵��Ϸ��� �ϴ� �������� �����̵�����

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D(); // ���� ī�޶� �ٶ󺸴¹��� ����
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from)); // ���� ��ġ���� �ٶ󺸴� �������� ȸ��

	Montages->PlayRoll();
}

void ASH_CActionPlayer::End_Roll()
{
	if (Action->IsUnarmedMode() == false) // ���⸦ ��� �ִٸ�
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
}

void ASH_CActionPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true; // �ڷΰ��鼭 �¿� ȸ������
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
}

void ASH_CActionPlayer::End_Backstep()
{
	if (Action->IsUnarmedMode()) // �����϶� Ǯ���ָ� �ȵ�.
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	State->SetIdleMode();
}

void ASH_CActionPlayer::OnFist()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetFistMode();
}

void ASH_CActionPlayer::OnOneHand()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetOneHandMode();
}

void ASH_CActionPlayer::OnTwoHand()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetTwoHandMode();
}

void ASH_CActionPlayer::OnWarp()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetWarpMode();
}

void ASH_CActionPlayer::OnFireStorm()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetFireStormMode();
}

void ASH_CActionPlayer::OnIceBall()
{
	CheckFalse_SH(State->IsIdleMode());

	Action->SetIceBallMode();
}

void ASH_CActionPlayer::OnDoAction()
{
	Action->DoAction();
}

void ASH_CActionPlayer::OnTarget()
{
	Target->ToggleTarget();
}

void ASH_CActionPlayer::OnTargetLeft()
{
	Target->ChangeTargetLeft();
}

void ASH_CActionPlayer::OnTargetRight()
{
	Target->ChangeTargetRight();
}

void ASH_CActionPlayer::OnAim()
{
	Action->DoAim();
}

void ASH_CActionPlayer::OffAim()
{
	Action->UndoAim();
}

void ASH_CActionPlayer::OnViewActionList()
{
	CheckFalse_SH(State->IsIdleMode());

	ActionList->SetVisibility(ESlateVisibility::Visible);

	GetController<APlayerController>()->bShowMouseCursor = true;
	GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f); // 10�� ������
}

void ASH_CActionPlayer::OffViewActionList()
{
	ActionList->SetVisibility(ESlateVisibility::Hidden);

	GetController<APlayerController>()->bShowMouseCursor = false;
	GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f); // ���󺹱�
}

void ASH_CActionPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}