#include "SH/Lectures/Actor/SH_SpawnActor_Cone.h"
#include "SH/SH_Global.h"

ASH_SpawnActor_Cone::ASH_SpawnActor_Cone()
{
	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Cone.SH_Cone'");
	Mesh->SetStaticMesh(mesh);
}