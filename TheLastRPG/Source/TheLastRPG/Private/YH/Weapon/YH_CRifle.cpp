#include "YH/Weapon/YH_CRifle.h"
#include "YH/Weapon/YH_IRifle.h"
#include "YH/Weapon/YH_CBullet.h"
#include "YH/CPlayer_YH.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "YH/Global_YH.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AYH_CRifle::AYH_CRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	CHelpers_YH::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	
	USkeletalMesh* mesh;
	CHelpers_YH::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers_YH::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/YongHwan/Montages/YH_Rifle_Grab_Montage.YH_Rifle_Grab_Montage'");
	CHelpers_YH::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/YongHwan/Montages/YH_Rifle_Ungrab_Montage.YH_Rifle_Ungrab_Montage'");
	CHelpers_YH::GetAsset<UAnimMontage>(&FireMontage, "AnimMontage'/Game/YongHwan/Montages/YH_Rifle_Fire_Montage.YH_Rifle_Fire_Montage'");

	CHelpers_YH::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers_YH::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	CHelpers_YH::GetAsset<UParticleSystem>(&ImpactParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	
	CHelpers_YH::GetAsset<USoundCue>(&FireSoundCue, "SoundCue'/Game/Lectures/Weapons/Sounds/YH_S_RifleShoot_Cue.YH_S_RifleShoot_Cue'");
	CHelpers_YH::GetClass<AYH_CBullet>(&BulletClass, "Blueprint'/Game/YongHwan/BP/YH_BP_CBullet.YH_BP_CBullet_C'");
	CHelpers_YH::GetAsset<UMaterialInstanceConstant>(&DecalMaterial, "MaterialInstanceConstant'/Game/Lectures/Weapons/Materials/M_Decal_Inst.M_Decal_Inst'");
}

void AYH_CRifle::Equip()
{
	YH_CheckTrue(bEquipped);
	YH_CheckTrue(bEquipping);

	bEquipping = true;
	//�÷��̾�� �� �ƴϴ�. �����ȴ�.
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void AYH_CRifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void AYH_CRifle::End_Equip()
{
	bEquipping = false;
}

void AYH_CRifle::Unequip()
{
	YH_CheckFalse(bEquipped);
	YH_CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void AYH_CRifle::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void AYH_CRifle::End_Unequip()
{
	bEquipping = false;
}

void AYH_CRifle::Begin_Aiming()
{
	bAiming = true;
}

void AYH_CRifle::End_Aiming()
{
	bAiming = false;
}

void AYH_CRifle::Begin_Fire()
{
	/*
���� �� �������̸� �ȵ���
���̹� ���ϸ� �ȵ���
���̾ Ʈ���϶�
*/
	YH_CheckFalse(bEquipped);
	YH_CheckTrue(bEquipping);
	YH_CheckFalse(bAiming);
	YH_CheckTrue(bFiring);

	//bFiring = true;

	Firing();
}

void AYH_CRifle::Firing()
{
	//�ѱ� ������ �ֳ� �ѱ� �˻�.
	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	YH_CheckNull(rifle);

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//ī�޶� ����ũ �־ ��Ÿ�� ���� �־ �̻��ϰ� ���� �ʿ����.
	//OwnerCharacter->PlayAnimMontage(FireMontage);

	ACPlayer_YH* player = Cast<ACPlayer_YH>(OwnerCharacter);
	if (!!player)
		player->PlayCameraShake();
	
	//attach���Ѽ� �÷����Ұ��̴�. - ��� ������Ʈ? ��������Ʈ,����(�̹��ִ�)���� �ѱ� ��ġ�� �����̴�. ��밣��
	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
		
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);
	
	if (!!BulletClass)
		GetWorld()->SpawnActor<AYH_CBullet>(BulletClass, muzzleLocation, direction.Rotation());
	
	//�Ȱ��� ����, �Ȱ��� ��ġ�� ����̴�.
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);

	//impact normal ���������� ��ֹ���, ECC�� ����.���� ���̳����� �ƴ϶�.
	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params))
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator, FVector(2));
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, rotator, 10.0f);
	}

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics)
				{
					direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					direction.Normalize();
					//���⺤�͸� �����ð�, ũ�� 1
					meshComponent->AddImpulseAtLocation(direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
					//��� �������� ������. �޽�������Ʈ�� ����* 100 �� ���� �ٰ��̴�. ���� �������� �ٰ��̴�. - �����ְڴ�.
					return;
				}
			}//if (!!meshComponent)
		}//if (!!staticMeshActor)
	}
}

void AYH_CRifle::End_Fire()
{
	//���綧 ���°�.
	//bFiring = false;
}

AYH_CRifle * AYH_CRifle::Spawn(UWorld * InWorld, ACharacter * InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;
	//AYH_RIfle ���·� �������ش�.
	return InWorld->SpawnActor<AYH_CRifle>(params);
}

// Called when the game starts or when spawned
void AYH_CRifle::BeginPlay()
{
	Super::BeginPlay();
	//� ���δ�
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	
}

// Called every frame
void AYH_CRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	YH_CheckFalse(bAiming);

	//���� �������� ���� �Ұ��̴�. ī�޶������
	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	YH_CheckNull(rifle);


	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);//�ڱ��ڽ� ����(��)
	params.AddIgnoredActor(OwnerCharacter);//�����ϰ� �ִ� ĳ����, �� �ΰ��� �����ϰ� �ɷ���

	FHitResult hitResult;////���̳��� ��ü�������°���
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		//����ƽ �޽þ��������� ĳ�����غ��� ����.
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics)//������ ������ �ִ� �ֳ�
				{
					rifle->OnFocus();

					return;
				}
			}//if (!!meshComponent) - if�� �������� ���� �� ���ش�.
		}//if (!!staticMeshActor)
	}

	rifle->OffFocus();
}

