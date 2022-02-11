#include "SH/Lectures/Collision/SH_Box.h"
#include "SH/Lectures/Collision/SH_MulticastTrigger.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ASH_Box::ASH_Box()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	UStaticMesh* mesh;
	SH_CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/SungHoon/Lectures/GunShooting/Meshes/SH_Cube.SH_Cube'");
	for (int32 i = 0; i < 3; ++i)
	{
		FString str;
		str.Append("Mesh_");
		str.Append(FString::FromInt(i + 1));

		SH_CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh[i], FName(str), Scene);

		Mesh[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		Mesh[i]->SetStaticMesh(mesh);
		Mesh[i]->SetSimulatePhysics(false); // 물리를 적용
	}
}

void ASH_Box::BeginPlay()
{
	Super::BeginPlay();

	TArray<ASH_MulticastTrigger*> triggers;
	SH_CHelpers::FindActors<ASH_MulticastTrigger>(GetWorld(), triggers);

	triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnPhysics"); //BindUFunction이 아님

	UMaterialInstanceConstant* material;
	SH_CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/SungHoon/Lectures/GunShooting/Materials/SH_M_Mesh_Inst.SH_M_Mesh_Inst'");

	for (int32 i = 0; i < 3; ++i)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(material, this);
		Mesh[i]->SetMaterial(0, Materials[i]);

		FTransform transform = Mesh[i]->GetComponentToWorld(); // 해당 컴포넌트의 월드 위치.
		WorldLocation[i] = transform.GetLocation(); // 최초 위치를 저장해둠.
	}
}

void ASH_Box::OnPhysics(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; ++i)
	{
		Materials[i]->SetVectorParameterValue("Color", FLinearColor(1, 1, 1));

		Mesh[i]->SetSimulatePhysics(false);
		Mesh[i]->SetWorldLocation(WorldLocation[i]);
	}

	Materials[InIndex]->SetVectorParameterValue("Color", InColor);
	Mesh[InIndex]->SetSimulatePhysics(true);
}