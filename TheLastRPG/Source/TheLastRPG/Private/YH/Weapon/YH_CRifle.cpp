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
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	//플레이어만이 꼭 아니다. 적도된다.
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
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

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
총을 안 장착중이면 안되지
에이밍 안하면 안되지
파이어링 트루일때
*/
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);
	CheckFalse(bAiming);
	CheckTrue(bFiring);

	//bFiring = true;

	Firing();
}

void AYH_CRifle::Firing()
{
	//총기 가지고 있나 총기 검사.
	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	CheckNull(rifle);

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//카메라 쉐이크 있어서 몽타주 굳이 넣어서 이상하게 만들 필요없다.
	//OwnerCharacter->PlayAnimMontage(FireMontage);

	ACPlayer_YH* player = Cast<ACPlayer_YH>(OwnerCharacter);
	if (!!player)
		player->PlayCameraShake();
	
	//attach시켜서 플레이할것이다. - 어느 컴포넌트? 총컴포넌트,소켓(이미있다)네임 총구 위치를 쓸것이다. 상대간격
	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
		
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);
	
	if (!!BulletClass)
		GetWorld()->SpawnActor<AYH_CBullet>(BulletClass, muzzleLocation, direction.Rotation());
	
	//똑같은 방향, 똑같은 위치로 쏠것이다.
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);

	//impact normal 맞은지점의 노멀방향, ECC를 쓴다.월드 다이나믹이 아니라.
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
					//방향벡터만 가져올것, 크기 1
					meshComponent->AddImpulseAtLocation(direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
					//어느 방향으로 나간다. 메시컴포넌트의 질량* 100 의 힘을 줄것이다. 힘의 방향으로 줄것이다. - 힘을주겠다.
					return;
				}
			}//if (!!meshComponent)
		}//if (!!staticMeshActor)
	}
}

void AYH_CRifle::End_Fire()
{
	//연사때 쓰는것.
	//bFiring = false;
}

AYH_CRifle * AYH_CRifle::Spawn(UWorld * InWorld, ACharacter * InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;
	//AYH_RIfle 형태로 리턴해준다.
	return InWorld->SpawnActor<AYH_CRifle>(params);
}

// Called when the game starts or when spawned
void AYH_CRifle::BeginPlay()
{
	Super::BeginPlay();
	//등에 붙인다
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	
}

// Called every frame
void AYH_CRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckFalse(bAiming);

	//적의 전방으로 보게 할것이다. 카메라방향을
	IYH_IRifle* rifle = Cast<IYH_IRifle>(OwnerCharacter);
	CheckNull(rifle);


	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);//자기자신 제거(총)
	params.AddIgnoredActor(OwnerCharacter);//소유하고 있는 캐릭터, 이 두개는 무시하고 걸려도

	FHitResult hitResult;////다이나믹 객체가져오는거지
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		//스테틱 메시액터인지는 캐스팅해보면 알지.
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics)//물리를 받을수 있는 애냐
				{
					rifle->OnFocus();

					return;
				}
			}//if (!!meshComponent) - if가 많을때는 조건 꼭 써준다.
		}//if (!!staticMeshActor)
	}

	rifle->OffFocus();
}

