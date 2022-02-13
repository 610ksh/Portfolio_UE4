#include "SH/Lecture2/Characters/SH_CEnemy.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Widgets/SH_CUserWidget_Name.h"
#include "SH/Lecture2/Widgets/SH_CUserWidget_Health.h"
#include "SH/SH_Global.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ASH_CEnemy::ASH_CEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	SH_CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	SH_CHelpers::CreateActorComponent<USH_CActionComponent>(this, &Action, "Action");
	SH_CHelpers::CreateActorComponent<USH_CMontagesComponent>(this, &Montages, "Montages");
	SH_CHelpers::CreateActorComponent<USH_CStatusComponent>(this, &Status, "Status");
	SH_CHelpers::CreateActorComponent<USH_CStateComponent>(this, &State, "State");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SungHoon/Lectures/ActionRPG/Character/Mesh/SH_Mannequin.SH_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	SH_CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SungHoon/Lectures/ActionRPG/Enemies/SH_ABP_CEnemy.SH_ABP_CEnemy_C'"); // _C
	GetMesh()->SetAnimClass(animInstance);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	TSubclassOf<USH_CUserWidget_Name> nameClass;
	SH_CHelpers::GetClass<USH_CUserWidget_Name>(&nameClass, "WidgetBlueprint'/Game/SungHoon/Lectures/ActionRPG/Widgets/WB_Name.WB_Name_C'"); // _C
	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameWidget->SetDrawSize(FVector2D(240, 30));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<USH_CUserWidget_Health> healthClass;
	SH_CHelpers::GetClass<USH_CUserWidget_Health>(&healthClass, "WidgetBlueprint'/Game/SungHoon/Lectures/ActionRPG/Widgets/WB_Health.WB_Health_C'"); // _C
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASH_CEnemy::BeginPlay()
{
	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;

	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/SungHoon/Lectures/ActionRPG/Character/Materials/SH_Action_Body_Inst.SH_Action_Body_Inst'");
	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/SungHoon/Lectures/ActionRPG/Character/Materials/SH_Action_ChestLogo_Inst.SH_Action_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ASH_CEnemy::OnStateTypeChanged);


	Super::BeginPlay();


	NameWidget->InitWidget();
	Cast<USH_CUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetNameText(GetActorLabel());

	HealthWidget->InitWidget();
	Cast<USH_CUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());

	Action->SetUnarmedMode();
}

void ASH_CEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASH_CEnemy::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ASH_CEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted:
		Hitted();
		break;
	case EStateType::Dead:
		Dead();
		break;
	}
}

float ASH_CEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageInstigator = EventInstigator; // 타격을 준 대상 = Player
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	SH_CLog::Log(Damage);

	State->SetHittedMode();

	return Status->GetHealth();
}

void ASH_CEnemy::Hitted()
{
	Status->SubHealth(DamageValue);
	Cast<USH_CUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());
	DamageValue = 0.0f;

	Status->SetStop();

	/// Dead
	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	Montages->PlayHitted();

	FVector start = GetActorLocation(); // Enemy
	FVector target = DamageInstigator->GetPawn()->GetActorLocation(); // Player
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));

	FVector direction = target - start;
	direction.Normalize();
	LaunchCharacter(-direction * LaunchAmount, true, false);

	ChangeColor(FLinearColor(1, 0, 0, 1));

	UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.1f, false);
}

void ASH_CEnemy::Dead()
{
	CheckFalse(State->IsDeadMode());
	Montages->PlayDead();
}

void ASH_CEnemy::Begin_Dead()
{
	Action->OffAllCollision();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASH_CEnemy::End_Dead()
{
	Destroy();
}

void ASH_CEnemy::RestoreColor()
{
	FLinearColor color = Action->GetCurrent()->GetEquipmentColor();

	ChangeColor(color);
}