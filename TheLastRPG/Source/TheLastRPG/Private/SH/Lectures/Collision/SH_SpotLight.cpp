#include "SH/Lectures/Collision/SH_SpotLight.h"
#include "SH/Lectures/Collision/SH_MulticastTrigger.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"

ASH_SpotLight::ASH_SpotLight()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	for (int32 i = 0; i < 3; ++i)
	{
		FString str;
		str.Append("SpotLights_");
		str.Append(FString::FromInt(i + 1));

		SH_CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLights[i], FName(str), Scene);

		SpotLights[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90,0,0)); // 위에서 아래로
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25.0f;
	}
}

void ASH_SpotLight::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<ASH_MulticastTrigger*> triggers;
	SH_CHelpers::FindActors<ASH_MulticastTrigger>(GetWorld(), triggers);

	triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnLightColor"); //BindUFunction이 아님

	if (triggers[0]->OnMultiLightBeginOverlap.IsBound())
		triggers[0]->OnMultiLightBeginOverlap.Broadcast(0, FLinearColor(0, 0, 1));
}

void ASH_SpotLight::OnLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; ++i)
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));

	SpotLights[InIndex]->SetLightColor(InColor);
}