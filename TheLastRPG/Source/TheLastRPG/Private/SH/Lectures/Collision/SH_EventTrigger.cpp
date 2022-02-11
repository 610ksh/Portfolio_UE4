#include "SH/Lectures/Collision/SH_EventTrigger.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_EventTrigger::ASH_EventTrigger()
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

void ASH_EventTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ASH_EventTrigger::ActorBeginOverlap);
}

void ASH_EventTrigger::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if(OnEventTrigger.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

		OnEventTrigger.Broadcast(index);
	}
}

