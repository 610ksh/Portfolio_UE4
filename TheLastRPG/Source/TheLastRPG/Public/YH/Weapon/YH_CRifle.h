// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YH_CRifle.generated.h"

UCLASS()
class THELASTRPG_API AYH_CRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYH_CRifle();
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	//bAiming controll- t,f
	void Begin_Aiming();
	void End_Aiming();


	void Begin_Fire();
	void Firing();
	void End_Fire();
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
		class UAnimMontage* FireMontage;
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* FlashParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* EjectParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class USoundCue* FireSoundCue;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		TSubclassOf<class AYH_CBullet> BulletClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UMaterialInstanceConstant* DecalMaterial;

public: 
	//�����ϴ°�. �����������ΰ�.
	static AYH_CRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	//���Ǻζ� ����� ���������� ����.
	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetEquipping() { return bEquipping; }
	FORCEINLINE bool GetAiming() { return bAiming; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;
	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;

};
