#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Explosion.generated.h"

UCLASS()
class THELASTRPG_API ASH_Explosion : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;
public:
	ASH_Explosion();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};