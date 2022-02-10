#include "YH/Weapon/YH_CBullet.h"
#include "YH/Global_YH.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"

AYH_CBullet::AYH_CBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers_YH::CreateComponent(this, &Mesh, "Mesh");
	CHelpers_YH::CreateActorComponent(this, &Projectile, "Projectile");
	UStaticMesh* mesh;
	CHelpers_YH::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/YongHwan/Meshes/YH_Sphere.YH_Sphere'");
	Mesh->SetStaticMesh(mesh); //�̰� �����ϱ� �Ⱥپ���. �׷��ϱ� ���׸��� �پ �ȳ���. �޽ð� �־�� �߶����� ���´�.(���δ�)
	
	UMaterialInstanceConstant* material; //�����ͺ����� ������ �������� ���� ���������� ���´�.
	CHelpers_YH::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_Bullet_Inst.YH_M_Bullet_Inst'");
	
	Mesh->SetMaterial(0, material);
	Mesh->SetRelativeScale3D(FVector(1.0f, 0.025f, 0.025f));

	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f; //2��
	Projectile->ProjectileGravityScale = 0.0f; //�߷��� ���ְڴ�.
	
	Projectile->SetUpdatedComponent(Mesh);
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AYH_CBullet::BeginPlay()
{
	Super::BeginPlay();
	//SetLifeSpan(3.0f);
	Mesh->OnComponentHit.AddDynamic(this, &AYH_CBullet::OnHit);
}

void AYH_CBullet::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//���������.
	Destroy();
}

