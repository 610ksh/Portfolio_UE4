#include "SH/Lectures/Collision/SH_MulticastTrigger.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_MulticastTrigger::ASH_MulticastTrigger()
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
	Text->Text = FText::FromString(GetName());
}

void ASH_MulticastTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ASH_MulticastTrigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASH_MulticastTrigger::ActorEndOverlap);
}

void ASH_MulticastTrigger::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OnMultiLightBeginOverlap.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		OnMultiLightBeginOverlap.Broadcast(index, color); // 여러개한테 전파한다는 브로드캐스트.
	}
}

void ASH_MulticastTrigger::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	
}