// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Characters/JG_CPlayer.h"
#include "JG/JG_Global.h"


#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

#include "JG/130_/Components/JG_COptionComponent.h"
#include "JG/130_/Components/JG_CStatusComponent.h"
#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/130_/Components/JG_CMontagesComponent.h"
#include "JG/130_/Components/JG_CActionComponent.h"

// Sets default values
AJG_CPlayer::AJG_CPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	JG_Helpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	
	JG_Helpers::CreateActorComponent<UJG_CMontagesComponent>(this, &Montages, "Montages");
	JG_Helpers::CreateActorComponent<UJG_COptionComponent>(this, &Option, "Option");
	JG_Helpers::CreateActorComponent<UJG_CStatusComponent>(this, &Status, "Status");
	JG_Helpers::CreateActorComponent<UJG_CStateComponent>(this, &State, "State");

	bUseControllerRotationYaw = false;

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	USkeletalMesh* mesh;
	JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/JongGyun/Character/JG_Mannequin.JG_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);


	TSubclassOf<UAnimInstance> animInstance;
	JG_Helpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/JongGyun/130_/Player/ABP_JG_CPlayer.ABP_JG_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);


	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	
	//GetCharacterMovement()->MaxWalkSpeed = ;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void AJG_CPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 칼 생성 - 맵에 등장만하고 캐릭터한테 붙이진 않음
//	Sword = AJG_CSword::Spawn(GetWorld(), this);



	State->OnStateTypeChanged.AddDynamic(this, &AJG_CPlayer::OnStateTypeChanged);
}

// Called every frame
void AJG_CPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJG_CPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJG_CPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJG_CPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AJG_CPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("LookUp", this, &AJG_CPlayer::OnVerticalLook);


	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &AJG_CPlayer::OnAvoid);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &AJG_CPlayer::OnOneHand);

}

void AJG_CPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void AJG_CPlayer::OnMoveRight(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void AJG_CPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AJG_CPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVecticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AJG_CPlayer::OnAvoid()
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

void AJG_CPlayer::OnStateTypeChanged(EStateType_JG InPrevType, EStateType_JG InNewType)
{
	switch (InNewType)
	{
	case EStateType_JG::Roll: Begin_Roll(); break;
	case EStateType_JG::Backstep: Begin_Backstep(); break;

	}
}

void AJG_CPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false; // 컨트롤러 꺼놓기 (구르는 방향으로만 움직이기 위함)
	GetCharacterMovement()->bOrientRotationToMovement = true; // 구르는 방향으로 잡아놓음

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D(); 
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from)); 
	 
	Montages->PlayRoll();
}

void AJG_CPlayer::End_Roll()
{
	//if (Action->IsUnarmedMode() == false)
	//{
	//	bUseControllerRotationYaw = true;
	//	GetCharacterMovement()->bOrientRotationToMovement = false;
	//}

	State->SetIdleMode();
}

void AJG_CPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true; // 컨트롤러를 켜놓긴 하는데 게임에서 어떻게 구현하느냐에 따라 끌수도 있을듯
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
}

void AJG_CPlayer::End_Backstep()
{
	//if (Action->IsUnarmedMode()) 
	//{
	//	bUseControllerRotationYaw = false;
	//	GetCharacterMovement()->bOrientRotationToMovement = true;
	//}

	State->SetIdleMode();
}


void AJG_CPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	//Action->SetOneHandMode();
}