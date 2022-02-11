#include "SH/Lectures/Collision/SH_SweepTrigger.h"
#include "SH/Lectures/Collision/SH_Explosion.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_SweepTrigger::ASH_SweepTrigger()
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

void ASH_SweepTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<ASH_Explosion*> explosions;
	SH_CHelpers::FindActors(GetWorld(), explosions);

	OnActorBeginOverlap.AddDynamic(explosions[0], &ASH_Explosion::ActorBeginOverlap);
}

