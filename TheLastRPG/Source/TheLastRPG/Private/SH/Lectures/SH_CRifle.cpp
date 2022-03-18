#include "SH/Lectures/SH_CRifle.h"
#include "SH/Lectures/SH_IRifle.h"
#include "SH/Lectures/SH_Player.h"
#include "SH/Lectures/SH_CBullet.h"
#include "SH/SH_Global.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Materials/MaterialInstanceConstant.h"

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
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SungHoon/Lectures/GunShooting/Weapons/SH_AR5.SH_AR5'");
	Mesh->SetSkeletalMesh(mesh);

	/// Montages
	SH_CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/SungHoon/Lectures/GunShooting/Character/Montage/SH_Rifle_Grab_Montage.SH_Rifle_Grab_Montage'");
	SH_CHelpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/SungHoon/Lectures/GunShooting/Character/Montage/SH_Rifle_Ungrab_Montage.SH_Rifle_Ungrab_Montage'");

	/// Particle
	SH_CHelpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	SH_CHelpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	SH_CHelpers::GetAsset<UParticleSystem>(&ImpactParticle, "ParticleSystem'/Game/Lectures/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	
	SH_CHelpers::GetAsset<USoundCue>(&FireSoundCue, "SoundCue'/Game/SungHoon/Lectures/GunShooting/Weapons/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	SH_CHelpers::GetClass<ASH_CBullet>(&BulletClass, "Blueprint'/Game/SungHoon/Lectures/GunShooting/Blueprints/SH_BP_CBullet.SH_BP_CBullet_C'");

	SH_CHelpers::GetAsset<UMaterialInstanceConstant>(&DecalMaterial, "MaterialInstanceConstant'/Game/SungHoon/Lectures/GunShooting/Weapons/Materials/M_Decal_Inst.M_Decal_Inst'");
}

#pragma region Equip Animation
void ASH_CRifle::Equip()
{
	CheckTrue_SH(bEquipped); // �̹� ��� �������̸� pass
	CheckTrue_SH(bEquipping); // ���� �����̶�� pass

	bEquipping = true;
	// OwnerCharacter�� �ϴ� ������ �ٸ� ĳ����(�� AI)�� ���� �� �־ �߸����� ������ ����.
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void ASH_CRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ASH_CRifle::End_Equip()
{
	bEquipping = false;
}
#pragma endregion

#pragma region Unequip Animation
void ASH_CRifle::Unequip()
{
	CheckFalse_SH(bEquipped); // ���������� �������� pass
	CheckTrue_SH(bEquipping); // ���� �����̶�� pass

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void ASH_CRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ASH_CRifle::End_Unequip()
{
	bEquipping = false;
}
#pragma endregion

#pragma region Aiming
void ASH_CRifle::Begin_Aiming()
{
	bAiming = true;
}
void ASH_CRifle::End_Aiming()
{
	bAiming = false;
}
#pragma endregion

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
	CheckFalse_SH(bAiming); // Aiming ���°� �ƴϸ� return

	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter);
	CheckNull_SH(rifle); // Rifle�� ISH_IRifle ����ϰ� ���� ������ return

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this); // rifle
	params.AddIgnoredActor(OwnerCharacter); // character

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor()); // �ε��� ���͸� ĳ�����غ�
		if (!!staticMeshActor) // ���������� ĳ���õȴٸ�
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics) // �浹ó���� �����ִٸ�
				{
					rifle->OnFocus();
					//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);
					return;
				}
			}
		}
	}

	rifle->OffFocus();
}

void ASH_CRifle::Begin_Fire()
{
	CheckFalse_SH(bEquipped); // ���������� ������ return
	CheckTrue_SH(bEquipping); // �������̸� return
	CheckFalse_SH(bAiming); // ���������� ������ return
	CheckTrue_SH(bFiring); // �߻����̸� return

	Firing();
}

void ASH_CRifle::Firing()
{
	// �θ�* ���� = �ڽ� 
	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter); // ó������ ����.
	CheckNull_SH(rifle); // �������� �ִٸ�

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	ASH_Player* player = Cast<ASH_Player>(OwnerCharacter);
	if (!!player)
		player->PlayCameraShake();

	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);

	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);

	/// �Ѿ� ����
	if (!!BulletClass)
		GetWorld()->SpawnActor<ASH_CBullet>(BulletClass, muzzleLocation, direction.Rotation());

	FCollisionQueryParams params;
	params.AddIgnoredActor(this); // rifle
	params.AddIgnoredActor(OwnerCharacter); // character

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params))
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator, FVector(2)); // źȯ ����Ʈ ����
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, rotator, 10.0f); // Decal ����
	}

	/// ���� �Ѿ�߸��� �ڵ�
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor()); // �ε��� ���͸� ĳ�����غ�
		if (!!staticMeshActor) // ���������� ĳ���õȴٸ�
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics) // �浹ó���� �����ִٸ�
				{
					direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					direction.Normalize(); // ���⺤��

					meshComponent->AddImpulseAtLocation(direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
					SH_CLog::Log("hit!");
					return;
				}
			}
		}
	}
}

void ASH_CRifle::End_Fire()
{

}