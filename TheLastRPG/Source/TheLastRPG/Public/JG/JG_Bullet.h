// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_Bullet.generated.h"

UCLASS()
class THELASTRPG_API AJG_Bullet : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UProjectileMovementComponent* Projectile;

	
public:	
	// Sets default values for this actor's properties
	AJG_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
