#include "SH/SH_CRifle.h"
#include "SH/SH_Global.h"
#include "SH/SH_IRifle.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
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
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	/// TODO Montages
	SH_CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/SungHoon/Character/Montage/SH_Rifle_Grab_Montage.SH_Rifle_Grab_Montage'");
	SH_CHelpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/SungHoon/Character/Montage/SH_Rifle_Ungrab_Montage.SH_Rifle_Ungrab_Montage'");

}

#pragma region Equip Animation
void ASH_CRifle::Equip()
{
	CheckTrue(bEquipped); // �̹� ��� �������̸� pass
	CheckTrue(bEquipping); // ���� �����̶�� pass

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
	CheckFalse(bEquipped); // ���������� �������� pass
	CheckTrue(bEquipping); // ���� �����̶�� pass

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

void ASH_CRifle::Begin_Aiming()
{
	bAiming = true;
}
void ASH_CRifle::End_Aiming()
{
	bAiming = false;
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
	CheckFalse(bAiming); // Aiming ���°� �ƴϸ� return

	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter);
	CheckNull(rifle); // Rifle�� ISH_IRifle ����ϰ� ���� ������ return

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
					return;
				}
			}
		}
	}

	rifle->OffFocus();
}

void ASH_CRifle::Begin_Fire()
{
	CheckFalse(bEquipped); // ���������� ������ return
	CheckTrue(bEquipping); // �������̸� return
	CheckFalse(bAiming); // ���������� ������ return
	CheckTrue(bFiring); // �߻����̸� return

	Firing();
}

void ASH_CRifle::Firing()
{
	// �θ�* ���� = �ڽ� 
	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter); // ó������ ����.
	CheckNull(rifle); // �������� �ִٸ�

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

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
					direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation(); // ���⺤��
					direction.Normalize();
					
					meshComponent->AddImpulseAtLocation(direction* meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
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
