#include "Release/AI/CEnemy.h"
#include "Release/Actions/CActionData.h"
#include "Release/Components/CActionComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Components/CMontageComponent.h"
#include "Release/Widgets/CUserWidget_Name.h"
#include "Release/Widgets/CUserWidget_Health.h"
#include "Release/Global.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	Helpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	Helpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");
	Helpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	Helpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	Helpers::CreateActorComponent<UCMontageComponent>(this, &Montages, "Montages");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SungHoon/Lectures/BP/Character/Character/Mesh/SH_SK_Mannequin.SH_SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	Helpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Lectures/BP/Character/SH_ABP2_Player.SH_ABP2_Player_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	TSubclassOf<UCUserWidget_Name> nameClass;
	Helpers::GetClass<UCUserWidget_Name>(&nameClass, "WidgetBlueprint'/Game/SungHoon/Projects/Widgets/WB_Name.WB_Name_C'");
	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameWidget->SetDrawSize(FVector2D(240, 30));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCUserWidget_Health> healthClass;
	Helpers::GetClass<UCUserWidget_Health>(&healthClass, "WidgetBlueprint'/Game/SungHoon/Projects/Widgets/WB_Health.WB_Health_C'");
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;
	Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/SungHoon/Projects/AI/Dummy/Materials/Dummy_Body.Dummy_Body'");
	Helpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/SungHoon/Projects/AI/Dummy/Materials/Dummy_ChestLogo.Dummy_ChestLogo'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);
	BodyMaterial->GetVectorParameterValue(L"BodyColor", originColor);

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	Super::BeginPlay();

	NameWidget->InitWidget();
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetNameText(GetActorLabel());

	HealthWidget->InitWidget();
	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());

	// Action-> UnarmedMode로 바꾸는것. 일단 빼놓음.
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Idle:
		break;
	case EStateType::Roll:
		break;
	case EStateType::Backstep:
		break;
	case EStateType::Equip:
		break;
	case EStateType::Unequip:
		break;
	case EStateType::Action:
		break;
	case EStateType::Hitted:
		Hitted();
		break;
	case EStateType::Max:
		break;
	default:
		break;
	}
}

void ACEnemy::RestoreColor()
{
	//FLinearColor color = Action->GetCurrentActionData()->GetEquipmentColor();
	ChangeColor(originColor);
}

void ACEnemy::Hitted()
{
	Status->SubHealth(DamageValue);
	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());
	DamageValue = 0;

	FVector start = GetActorLocation();
	FVector target = DamageInstigator->GetPawn()->GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
	DamageInstigator = NULL;
	
	FVector direction = target - start;
	direction.Normalize();
	LaunchCharacter(-direction * LaunchAmount, true, false);

	ChangeColor(FLinearColor(1, 0, 0, 1));
	UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.1f, false);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageInstigator = EventInstigator;
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CLog::Log(DamageValue);
	CLog::Print(DamageValue);

	State->SetHittedMode();

	return Status->GetHealth();
}