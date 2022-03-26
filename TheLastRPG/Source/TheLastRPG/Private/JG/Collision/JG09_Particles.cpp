// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Collision/JG09_Particles.h"
#include "JG/Collision/JG08_EventTrigger.h"
#include "JG/JG_Global.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AJG09_Particles::AJG09_Particles()
{
	JG_Helpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	JG_Helpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	JG_Helpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	JG_Helpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");


}

// Called when the game starts or when spawned
void AJG09_Particles::BeginPlay()
{
	Super::BeginPlay();

	TArray<AJG08_EventTrigger*> triggers;
	JG_Helpers::FindActors<AJG08_EventTrigger>(GetWorld(), triggers);
	triggers[0]->OnEventTrigger.AddUFunction(this, "PlayParticle"); //BindUFunction이 아님

	//if (triggers[0]->OnEventTrigger.IsBound()) // 외부 접근 확인하는 if문
	//	triggers[0]->OnEventTrigger.Broadcast(0, FLinearColor(0, 0, 1));
}

void AJG09_Particles::PlayParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}