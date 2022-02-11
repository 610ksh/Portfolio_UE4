#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_CBullet.generated.h"

UCLASS()
class THELASTRPG_API ASH_CBullet : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:	
	ASH_CBullet();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
