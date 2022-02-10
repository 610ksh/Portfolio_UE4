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
	Mesh->SetStaticMesh(mesh); //이거 없으니까 안붙었다. 그러니까 메테리얼 붙어도 안나와. 메시가 있어야 발라져서 나온다.(보인다)
	
	UMaterialInstanceConstant* material; //포인터변수만 나오면 참조되지 않은 지역변수라 나온다.
	CHelpers_YH::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_Bullet_Inst.YH_M_Bullet_Inst'");
	
	Mesh->SetMaterial(0, material);
	Mesh->SetRelativeScale3D(FVector(1.0f, 0.025f, 0.025f));

	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f; //2만
	Projectile->ProjectileGravityScale = 0.0f; //중력은 안주겠다.
	
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
	//끝나면삭제.
	Destroy();
}

