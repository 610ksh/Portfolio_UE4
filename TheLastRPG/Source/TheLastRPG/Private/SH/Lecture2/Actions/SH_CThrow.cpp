#include "SH/Lecture2/Actions/SH_CThrow.h"
#include "SH/SH_Global.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASH_CThrow::ASH_CThrow()
{
	SH_CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	SH_CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Sphere);
	SH_CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 4000.0f;
	Projectile->MaxSpeed = 8000.0f;
	Projectile->ProjectileGravityScale = 0.0f;
}

void ASH_CThrow::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<USphereComponent*> components;
	GetComponents<USphereComponent>(components);

	for (USphereComponent* sphere : components)
		sphere->OnComponentBeginOverlap.AddDynamic(this, &ASH_CThrow::OnComponentBeginOverlap);
}

void ASH_CThrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(SweepResult.Location);
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(SweepResult);

	Destroy();
}