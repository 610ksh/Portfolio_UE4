#include "SH/Lectures/Collision/SH_Override.h"
#include "SH/Lectures/SH_Player.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_Override::ASH_Override()
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

void ASH_Override::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ASH_Override::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASH_Override::ActorEndOverlap);
}

void ASH_Override::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangeColorRed();
}

void ASH_Override::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangeColorWhite();
}

void ASH_Override::ChangeColorWhite_Implementation()
{
	ASH_Player* player = Cast<ASH_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->ChangeColor(FLinearColor(0, 0, 1)); // blue
}