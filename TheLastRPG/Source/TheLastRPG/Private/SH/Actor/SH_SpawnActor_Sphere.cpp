// Fill out your copyright notice in the Description page of Project Settings.


#include "SH/Actor/SH_SpawnActor_Sphere.h"
#include "SH/SH_Global.h"


ASH_SpawnActor_Sphere::ASH_SpawnActor_Sphere()
{
	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Sphere.SH_Sphere'");
	Mesh->SetStaticMesh(mesh);
}