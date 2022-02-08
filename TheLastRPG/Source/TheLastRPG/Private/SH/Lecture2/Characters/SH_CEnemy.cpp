#include "SH/Lecture2/Characters/SH_CEnemy.h"
#include "SH/SH_Global.h"

ASH_CEnemy::ASH_CEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASH_CEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASH_CEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASH_CEnemy::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}