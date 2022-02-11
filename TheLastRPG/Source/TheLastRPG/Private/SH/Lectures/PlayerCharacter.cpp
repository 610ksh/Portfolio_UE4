#include "SH/Lectures/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//m_Movement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("MOVEMENT")); //o

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'"));

	//if (SM.Succeeded())
	//{
	//	this->GetMesh()->SetSkeletalMesh(SM.Object);
	//}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	/// LOG (카테고리, 로깅 수준, 형식, 인자)
	UE_LOG(LogTemp, Warning, TEXT("Begin Play %d"), 3);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime);

	//AddActorLocalRotation(FRotator(0.f, m_RotateSpeed * DeltaTime, 0.f));

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown_SH"), this, &APlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_SH"), this, &APlayerCharacter::LeftRight);
}

void APlayerCharacter::UpDown(float value)
{
	if (value == 0.f)
		return;
	AddMovementInput(GetActorForwardVector(), value);
	
	UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), value);
}

void APlayerCharacter::LeftRight(float value)
{
	if (value == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), value);

	UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), value);
}

