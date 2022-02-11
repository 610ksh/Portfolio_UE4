// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/JG_Bullet.h"
#include "JG/JG_Global.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AJG_Bullet::AJG_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent(this, &Mesh, "Mesh");
	JG_Helpers::CreateActorComponent(this, &Projectile, "Projectile");

	UStaticMesh* mesh;
	JG_Helpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/JongGyun/Meshs/M_Sphere.M_Sphere'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	JG_Helpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/JongGyun/Materials/M_Bullet_Inst.M_Bullet_Inst'");
	Mesh->SetMaterial(0, material);

	Mesh->SetRelativeScale3D(FVector(1.0f, 0.025f, 0.025f));

	Projectile->InitialSpeed = 2e+4f; // 2만
	Projectile->MaxSpeed = 2e+4f;
	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->SetUpdatedComponent(Mesh);

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AJG_Bullet::BeginPlay()
{
	Super::BeginPlay();

	//SetLifeSpan(3.0f); // 위로 위치 이동

	Mesh->OnComponentHit.AddDynamic(this, &AJG_Bullet::OnHit);
}

void AJG_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
