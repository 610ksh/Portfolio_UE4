#include "SH/Lecture2/Actors/SH_CPatrolPath.h"
#include "SH/SH_Global.h"

#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

ASH_CPatrolPath::ASH_CPatrolPath()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<USplineComponent>(this, &Spline, "Spline", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Spline->SetRelativeLocation(FVector(0, 0, 30));

	Text->SetRelativeLocation(FVector(0, 0, 120));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;
}

void ASH_CPatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
	Text->SetVisibility(false);
}

void ASH_CPatrolPath::OnConstruction(const FTransform& Transform)
{
	Text->Text = FText::FromString(GetActorLabel());

	Spline->SetClosedLoop(bLoop);
}