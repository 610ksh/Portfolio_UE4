#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Particles.generated.h"

UCLASS()
class THELASTRPG_API ASH_Particles : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* Particles[3];

public:	
	ASH_Particles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void PlayParticle(int32 InIndex);
};
