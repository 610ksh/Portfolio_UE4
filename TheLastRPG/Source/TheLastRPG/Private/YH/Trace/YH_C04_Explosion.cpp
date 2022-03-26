#include "YH/Trace/YH_C04_Explosion.h"
#include "Particles/ParticleSystemComponent.h"
#include "YH/Global_YH.h"


AYH_C04_Explosion::AYH_C04_Explosion()
{
	CHelpers_YH::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");

	UParticleSystem* particle;
	CHelpers_YH::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/Lectures/Effects/P_Explosion2.P_Explosion2'");
	Particle->SetTemplate(particle);
	Particle->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AYH_C04_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AYH_C04_Explosion::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	Particle->ResetParticles();
	Particle->SetActive(true);

	//* start (연속파티클충돌 코드)
	FVector start = GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitResults;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 200, queries, false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResults, true))
	{
		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (!!meshComponent) ////linear는 퍼지면서 힘이 줄어드는것 
				meshComponent->AddRadialImpulse(GetActorLocation(), 1000, meshComponent->GetMass() * 700.0f, ERadialImpulseFalloff::RIF_Linear);
		}
	}
	//* end (연속파티클충돌 코드)
}

