// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Collision/JG04_Light.h"
#include "JG/JG_Global.h"
#include "JG/Collision/JG03_Trigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"


// Ctrl+tap = 창바꾸기
// Ctrl+k+o = 헤더 cpp 왔다갔다
// Ctrl + 화살표 = 단어단위 왔다갔다
// Sets default values
AJG04_Light::AJG04_Light()
{
	JG_Helpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	JG_Helpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	JG_Helpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);
	JG_Helpers::CreateComponent<UPointLightComponent>(this, &Light2, "Light2", Scene);


	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	Light->Intensity = 1e+4f;
	Light->AttenuationRadius = 200;
	Light->LightColor = FColor(255, 128, 50);

	Light2->SetRelativeLocation(FVector(0, 200, 0));
	Light2->Intensity = 1e+4f;
	Light2->AttenuationRadius = 200;
	Light2->LightColor = FColor(255, 128, 50);
}

// Called when the game starts or when spawned
void AJG04_Light::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false); 
	Light2->SetVisibility(false);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJG03_Trigger::StaticClass(), actors);

	JG_CheckFalse(actors.Num() > 0);

	AJG03_Trigger* trigger = Cast<AJG03_Trigger>(actors[0]); 
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
	trigger->OnBoxLightRandomBeginOverlap.BindUFunction(this, "OnRandomLight");

}


void AJG04_Light::OnLight()
{
	Light->SetVisibility(true);
}

void AJG04_Light::OffLight()
{
	Light->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString AJG04_Light::OnRandomLight(FLinearColor InColor)
{
	Light2->SetVisibility(true);
	Light2->SetLightColor(InColor);

	return InColor.ToString();
}