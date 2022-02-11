#include "SH/Lectures/Collision/SH_Cube.h"
#include "SH/SH_Global.h"
#include "Components/StaticMeshComponent.h"

ASH_Cube::ASH_Cube()
{
	SH_CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Cube.SH_Cube'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
}

void ASH_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}
