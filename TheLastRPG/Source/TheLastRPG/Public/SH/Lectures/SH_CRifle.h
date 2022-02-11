// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_CRifle.generated.h"

UCLASS()
class THELASTRPG_API ASH_CRifle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* GrabMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* UngrabMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* FlashParticle;
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* EjectParticle;
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class USoundCue* FireSoundCue;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		TSubclassOf<class ASH_CBullet> BulletClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UMaterialInstanceConstant* DecalMaterial;

public:
	// 자기 자료형을 생성해서 리턴함. static이라 독립적임. 월드와 캐릭터를 받아준다.
	static ASH_CRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetEquipping() { return bEquipping; }
	FORCEINLINE bool GetAiming() { return bAiming; }

public:	
	ASH_CRifle();

	/// Equip
	void Equip();
	void Begin_Equip();
	void End_Equip();
	/// Unequip
	void Unequip();
	void Begin_Unequip();
	void End_Unequip();
	/// Aiming
	void Begin_Aiming();
	void End_Aiming();
	/// Fire
	void Begin_Fire();
	void Firing();
	void End_Fire();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
};
