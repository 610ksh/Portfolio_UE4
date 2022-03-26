#include "YH/Collision/YH_C09_Particles.h"
#include "YH/Global_YH.h"
#include "YH/Collision/YH_C08_EventTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AYH_C09_Particles::AYH_C09_Particles()
{
	CHelpers_YH::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers_YH::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	CHelpers_YH::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	CHelpers_YH::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	CHelpers_YH::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");

}

void AYH_C09_Particles::BeginPlay()
{
	Super::BeginPlay();
	TArray<AYH_C08_EventTrigger*> triggers;
	CHelpers_YH::FindActors<AYH_C08_EventTrigger>(GetWorld(), triggers);
	triggers[0]->OnEventTrigger.AddUFunction(this, "PlayParticle");
}

void AYH_C09_Particles::PlayParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}



