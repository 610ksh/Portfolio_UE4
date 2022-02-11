#include "SH/Lectures/SH_CBullet.h"
#include "SH/SH_Global.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ASH_CBullet::ASH_CBullet()
{
	SH_CHelpers::CreateComponent(this, &Mesh, "Mesh");
	SH_CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Sphere.SH_Sphere'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	SH_CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/SungHoon/Lectures/GunShooting/Materials/SH_M_Bullet_Inst.SH_M_Bullet_Inst'");
	Mesh->SetMaterial(0, material);
	Mesh->SetRelativeScale3D(FVector(1.0f, 0.025f, 0.025f));

	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f;
	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->SetUpdatedComponent(Mesh);

	InitialLifeSpan = 3.0f; // 생존시간 3초
}

void ASH_CBullet::BeginPlay()
{
	Super::BeginPlay();

	// 어떤 물체와 충돌했을때 발동.
	Mesh->OnComponentHit.AddDynamic(this, &ASH_CBullet::OnHit);
}

void ASH_CBullet::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	SH_CLog::Print("Destroy");
	Destroy();
}
