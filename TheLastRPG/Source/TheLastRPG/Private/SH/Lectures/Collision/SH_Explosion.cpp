#include "SH/Lectures/Collision/SH_Explosion.h"
#include "SH/SH_Global.h"
#include "Particles/ParticleSystemComponent.h"

ASH_Explosion::ASH_Explosion()
{
	SH_CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");

	UParticleSystem* particle;
	SH_CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	Particle->SetTemplate(particle); // 템플릿 부분에 할당해주자.
	Particle->bAutoActivate = false; // 바로 자동으로 실행되는거 끔.
}

void ASH_Explosion::BeginPlay()
{
	Super::BeginPlay();
}

void ASH_Explosion::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	Particle->ResetParticles(); // 리셋해줘야함. 기존에 하던거 초기화됨.
	Particle->SetActive(true); // 들어왔을때 실행
	 
	FVector start = GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);

	TArray<FHitResult> hitResults;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 200, queries, false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResults, true))
	{
		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (!!meshComponent)
				meshComponent->AddRadialImpulse(GetActorLocation(), 1000, meshComponent->GetMass()*800.0f, ERadialImpulseFalloff::RIF_Linear);
		}

	}
}
