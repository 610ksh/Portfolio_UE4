#include "SH/Collision/SH_Trigger.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_Trigger::ASH_Trigger()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // ��ü�� �̸�, String�� Text�� ��ȯ����.
}

// Called when the game starts or when spawned
void ASH_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ASH_Trigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASH_Trigger::ActorEndOverlap);
}

void ASH_Trigger::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OnBoxLightBeginOverlap.IsBound()) // � ����� �Լ��� �ִ���
		OnBoxLightBeginOverlap.Execute(); // �����϶�.

	if (OnBoxLightRandomBeginOverlap.IsBound())
	{
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		FString str = OnBoxLightRandomBeginOverlap.Execute(color);
		SH_CLog::Log(str);
	}
}

void ASH_Trigger::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OnBoxLightEndOverlap.IsBound()) // � ����� �Լ��� �ִ���
		OnBoxLightEndOverlap.Execute(); // �����϶�.
}