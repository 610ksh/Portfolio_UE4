#include "SH/Lectures/Collision/SH_ComponentBeginOverlap.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ASH_ComponentBeginOverlap::ASH_ComponentBeginOverlap()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // 부모가 될거니까 부모를 비어둠.
	SH_CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	SH_CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Scene);

	Box->SetRelativeScale3D(FVector(3)); // x,y,z에 3배씩 들어감
	Box->bHiddenInGame = false; // 지역변수를 사용하는게 더 좋음. Set이 있어도

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // 객체의 이름, String을 Text로 변환해줌.

	PointLight->SetLightColor(FLinearColor::Red);
}

void ASH_ComponentBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false); // 처음엔 끔
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASH_ComponentBeginOverlap::ComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ASH_ComponentBeginOverlap::ComponentEndOverlap);
}

void ASH_ComponentBeginOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true); // 처음엔 켬
}

void ASH_ComponentBeginOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false); // 처음엔 끔
}