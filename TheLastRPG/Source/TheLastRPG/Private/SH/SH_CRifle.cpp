#include "SH/SH_CRifle.h"
#include "SH/SH_Global.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ASH_CRifle* ASH_CRifle::Spawn(class UWorld* InWorld, class ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<ASH_CRifle>(params);
}

ASH_CRifle::ASH_CRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/data/119/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	/// TODO Montages
	SH_CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/SungHoon/Montages/SH_Rifle_Grab_Montage.SH_Rifle_Grab_Montage'");
	SH_CHelpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/SungHoon/Montages/SH_Rifle_Ungrab_Montage.SH_Rifle_Ungrab_Montage'");

}

void ASH_CRifle::Equip()
{
}

void ASH_CRifle::Begin_Equip()
{
}

void ASH_CRifle::End_Equip()
{
}

void ASH_CRifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner()); // ���� �ڽ��� �������� ������
												  
	// ���� ĳ������ �޽÷ΰ��� ���Ͽ� ���� ������ �����ϴ� �Լ�.
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ASH_CRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

