#include "SH/Collision/SH_ComponentBeginOverlap.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ASH_ComponentBeginOverlap::ASH_ComponentBeginOverlap()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // �θ� �ɰŴϱ� �θ� ����.
	SH_CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	SH_CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Scene);

	Box->SetRelativeScale3D(FVector(3)); // x,y,z�� 3�辿 ��
	Box->bHiddenInGame = false; // ���������� ����ϴ°� �� ����. Set�� �־

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // ��ü�� �̸�, String�� Text�� ��ȯ����.

	PointLight->SetLightColor(FLinearColor::Red);
}

void ASH_ComponentBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false); // ó���� ��
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASH_ComponentBeginOverlap::ComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ASH_ComponentBeginOverlap::ComponentEndOverlap);
}

void ASH_ComponentBeginOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true); // ó���� ��
}

void ASH_ComponentBeginOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false); // ó���� ��
}