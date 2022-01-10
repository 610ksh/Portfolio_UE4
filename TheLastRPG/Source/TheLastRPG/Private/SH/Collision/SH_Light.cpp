#include "SH/Collision/SH_Light.h"
#include "SH/SH_Global.h"
#include "SH/Collision/SH_Trigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ASH_Light::ASH_Light()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // �θ� �ɰŴϱ� �θ� ����.
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	SH_CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // ��ü�� �̸�, String�� Text�� ��ȯ����.

	Light->Intensity = 1e+4f; // e : ���� -> 10^4 ǥ�����. 10,000
	//1e-6f = 10^-6 = 0.000001 : 5���� 0 1���� 1
	Light->AttenuationRadius = 200; // �ݰ�
	Light->LightColor = FColor(255, 128, 50); // (255,255,255) char
}

void ASH_Light::BeginPlay()
{
	Super::BeginPlay();
	
	Light->SetVisibility(false); // ó���� ��

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASH_Trigger::StaticClass(), actors);

	CheckFalse(actors.Num() > 0); // �迭�� ũ�Ⱑ 0�̸� return ���ѹ���.

	ASH_Trigger* trigger = Cast<ASH_Trigger>(actors[0]); // 1���� ã�����Ŷ� 0�� ����.
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
}

void ASH_Light::OnLight()
{
	Light->SetVisibility(true);
}

void ASH_Light::OffLight()
{
	Light->SetVisibility(false); 
}