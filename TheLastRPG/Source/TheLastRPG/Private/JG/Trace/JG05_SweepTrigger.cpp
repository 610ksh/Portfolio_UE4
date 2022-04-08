// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Trace/JG05_SweepTrigger.h"
#include "JG/JG_Global.h"
#include "JG/Trace/JG04_Explosion.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AJG05_SweepTrigger::AJG05_SweepTrigger()
{
	JG_Helpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	JG_Helpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	JG_Helpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;


	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());
}

// Called when the game starts or when spawned
void AJG05_SweepTrigger::BeginPlay()
{
	Super::BeginPlay();

	TArray<AJG04_Explosion*> explosions;
	JG_Helpers::FindActors(GetWorld(), explosions);

	OnActorBeginOverlap.AddDynamic(explosions[0], &AJG04_Explosion::ActorBeginOverlap);
}

