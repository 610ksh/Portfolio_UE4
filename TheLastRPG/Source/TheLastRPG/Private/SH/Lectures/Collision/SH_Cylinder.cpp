#include "SH/Lectures/Collision/SH_Cylinder.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

ASH_Cylinder::ASH_Cylinder()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	SH_CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Cylinder.SH_Cylinder'");

	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(1, 1, 2.5f));
}

void ASH_Cylinder::BeginPlay()
{
	Super::BeginPlay();


}