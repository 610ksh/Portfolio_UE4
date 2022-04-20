#include "SH/Lectures/Collision/SH_Light.h"
#include "SH/Lectures/Collision/SH_Trigger.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ASH_Light::ASH_Light()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // 부모가 될거니까 부모를 비어둠.
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	SH_CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);
	SH_CHelpers::CreateComponent<UPointLightComponent>(this, &Light2, "Light2", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // 객체의 이름, String을 Text로 변환해줌.

	Light->SetRelativeLocation(FVector(0, -100, 0)); // 왼쪽으로 -100
	//1e-6f = 10^-6 = 0.000001 : 5개의 0 1개는 1
	Light->Intensity = 1e+4f; // e : 지수 -> 10^4 표기법임. 10,000
	Light->AttenuationRadius = 200; // 반경
	Light->LightColor = FColor(255, 128, 50); // (255,255,255) char

	Light2->SetRelativeLocation(FVector(0, 100, 0)); // 오른쪽으로 100만큼
	Light2->Intensity = 1e+4f;
	Light2->AttenuationRadius = 200;
	Light2->LightColor = FColor(0, 255, 255);
}

void ASH_Light::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false); // 처음엔 끔
	Light2->SetVisibility(false); // 처음엔 끔

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASH_Trigger::StaticClass(), actors);

	SH_CheckFalse(actors.Num() > 0); // 배열의 크기가 0이면 return 시켜버림.

	ASH_Trigger* trigger = Cast<ASH_Trigger>(actors[0]); // 1개만 찾았을거라 0번 고정.
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
	trigger->OnBoxLightRandomBeginOverlap.BindUFunction(this, "OnRandomLight");
}

void ASH_Light::OnLight()
{
	Light->SetVisibility(true);
}

void ASH_Light::OffLight()
{
	Light->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString ASH_Light::OnRandomLight(FLinearColor InColor)
{
	Light2->SetLightColor(InColor); // 색깔 지정
	Light2->SetVisibility(true); // 켜준다

	// float 255
	return InColor.ToString(); // 현재 색상의 번호를 넘겨준다.
}