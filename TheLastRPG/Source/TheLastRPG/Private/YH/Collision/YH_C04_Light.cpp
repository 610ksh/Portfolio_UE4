#include "YH/Collision/YH_C04_Light.h"
#include "YH/Collision/YH_C03_Trigger.h"
#include "YH/Global_YH.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

AYH_C04_Light::AYH_C04_Light()
{
	CHelpers_YH::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers_YH::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers_YH::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);
	CHelpers_YH::CreateComponent<UPointLightComponent>(this, &Light2, "Light2", Scene);


	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	//1e+4f = 10^4 = 10000
	//1e-6f = 10^-6 = 0.000001;
	Light->Intensity = 1e+4f;
	Light->AttenuationRadius = 200;
	Light->LightColor = FColor(255, 128, 50);

	Light2->SetRelativeLocation(FVector(0, 200, 0));
	Light2->Intensity = 1e+4f;
	Light2->AttenuationRadius = 200;
	Light2->LightColor = FColor(255, 128, 50);

	
}
//박스 붙였다.
void AYH_C04_Light::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);
	Light2->SetVisibility(false);


	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AYH_C03_Trigger::StaticClass(), actors);
	YH_CheckFalse(actors.Num() > 0);

	AYH_C03_Trigger* trigger = Cast<AYH_C03_Trigger>(actors[0]);
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
	trigger->OnBoxLightRandomBeginOverlap.BindUFunction(this, "OnRandomLight");

}

void AYH_C04_Light::OnLight()
{
	Light->SetVisibility(true);
}

void AYH_C04_Light::OffLight()
{
	Light->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString AYH_C04_Light::OnRandomLight(FLinearColor InColor)
{
	Light2->SetVisibility(true);
	Light2->SetLightColor(InColor);

	return InColor.ToString();
}


