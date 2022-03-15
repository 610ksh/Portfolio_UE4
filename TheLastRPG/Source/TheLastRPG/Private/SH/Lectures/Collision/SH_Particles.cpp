#include "SH/Lectures/Collision/SH_Particles.h"
#include "SH/Lectures/Collision/SH_EventTrigger.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"

ASH_Particles::ASH_Particles()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	SH_CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/Lectures/Effects/P_AOE_Ice_CircleAttack.P_AOE_Ice_CircleAttack'");
	SH_CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/Lectures/Effects/P_Cube_Mesh_Test.P_Cube_Mesh_Test'");
	SH_CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
}

void ASH_Particles::BeginPlay()
{
	Super::BeginPlay();

	TArray<ASH_EventTrigger*> triggers;
	SH_CHelpers::FindActors<ASH_EventTrigger>(GetWorld(), triggers);
	triggers[0]->OnEventTrigger.AddUFunction(this, "PlayParticle"); //BindUFunction이 아님

	/// 이벤트는 아래처럼 외부에서 사용할 수 없음. 델리게이트만 가능.
	/*if (triggers[0]->OnEventTrigger.IsBound())
		triggers[0]->OnEventTrigger.Broadcast(0, FLinearColor(0, 0, 1));*/
}

void ASH_Particles::PlayParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation()); 

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}