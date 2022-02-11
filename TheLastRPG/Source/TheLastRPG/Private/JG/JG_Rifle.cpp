// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/JG_Rifle.h"
#include "JG/JG_IRifle.h"
#include "JG/JG_Global.h"
#include "JG/JG_Player.h"
#include "JG/JG_Bullet.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Materials/MaterialInstanceConstant.h"


AJG_Rifle* AJG_Rifle::Spawn(class UWorld* InWorld, class ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<AJG_Rifle>(params);
}

// Sets default values
AJG_Rifle::AJG_Rifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	JG_Helpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/JongGyun/Character/Animation/Montage/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	JG_Helpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/JongGyun/Character/Animation/Montage/Rifle_Ungrab_Montage.Rifle_Ungrab_Montage'");
	JG_Helpers::GetAsset<UAnimMontage>(&FireMontage, "AnimMontage'/Game/JongGyun/Character/Animation/Montage/Rifle_Fire_Montage.Rifle_Fire_Montage'");
	JG_Helpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/JongGyun/etc/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	JG_Helpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/JongGyun/etc/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	JG_Helpers::GetAsset<UParticleSystem>(&ImpactParticle, "ParticleSystem'/Game/JongGyun/etc/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	JG_Helpers::GetAsset<USoundCue>(&FireSoundCue, "SoundCue'/Game/JongGyun/etc/Sound/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	JG_Helpers::GetClass<AJG_Bullet>(&BulletClass, "Blueprint'/Game/JongGyun/Actor/BP_JG_Bullet.BP_JG_Bullet_C'");
	JG_Helpers::GetAsset<UMaterialInstanceConstant>(&DecalMaterial, "MaterialInstanceConstant'/Game/JongGyun/etc/129/Texture/M_Hole_Inst.M_Hole_Inst'");
	
}

void AJG_Rifle::Equip()
{
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void AJG_Rifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void AJG_Rifle::End_Equip()
{

	bEquipping = false;
}

void AJG_Rifle::Unequip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void AJG_Rifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void AJG_Rifle::End_Unequip()
{
	bEquipping = false;
}

void AJG_Rifle::Begin_Aiming()
{
	bAiming = true;
}

void AJG_Rifle::End_Aiming()
{
	bAiming = false;
}



// Called when the game starts or when spawned
void AJG_Rifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

// Called every frame
void AJG_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bAiming);
	IJG_IRifle* rifle = Cast<IJG_IRifle>(OwnerCharacter);
	CheckNull(rifle);

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);

	

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
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
					rifle->OnFocus();
					return;
				}
			}//meshC
		}//staticM
	}
	rifle->OffFocus();
}


void AJG_Rifle::Begin_Fire()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);
	CheckFalse(bAiming);
	CheckTrue(bFiring);

	//bFiring = true;

	Firing();
}

void AJG_Rifle::Firing()
{
	IJG_IRifle* rifle = Cast<IJG_IRifle>(OwnerCharacter);
	CheckNull(rifle);

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	// 카메라가 한들리는 효과가 아래에 있어서 이놈을 굳이 쓸 필요가 없음
	//OwnerCharacter->PlayAnimMontage(FireMontage);

	AJG_Player* player = Cast<AJG_Player>(OwnerCharacter);
	if (!!player)
		player->PlayCameraShake();


	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation:: KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation:: KeepRelativeOffset);

	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);

	if (!!BulletClass)
		GetWorld()->SpawnActor<AJG_Bullet>(BulletClass, muzzleLocation, direction.Rotation());


	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	//start지점부터 end지점까지 보이는건 모두 다 이펙트 효과 줌
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params))
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();//임팩트 노말이란? 충돌체에 대한 수직 방향(수직벡터)를 가져옴. 반사효과를 위한것 같다.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator,FVector(2));
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

					meshComponent->AddImpulseAtLocation(direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
					return;
				}
			}//meshC
		}//staticM
	}
}

void AJG_Rifle::End_Fire()
{
	//bFiring = false;
}