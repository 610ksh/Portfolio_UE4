// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Characters/JG_CPlayer.h"
#include "JG/JG_Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "JG/130_/Components/JG_COptionComponent.h"
// Sets default values
AJG_CPlayer::AJG_CPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	JG_Helpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	
	JG_Helpers::CreateActorComponent<UJG_COptionComponent>(this, &Option, "Option");

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
	SpringArm->TargetArmLength = 200.0f;
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
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AJG_CPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AJG_CPlayer::OnVerticalLook);

}

void AJG_CPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AJG_CPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AJG_CPlayer::OnHorizontalLook(float Axis)
{

}

void AJG_CPlayer::OnVerticalLook(float Axis)
{

}

