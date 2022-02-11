// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_Rifle.generated.h"

UCLASS()
class THELASTRPG_API AJG_Rifle : public AActor
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
	TSubclassOf<class AJG_Bullet> BulletClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	class UMaterialInstanceConstant* DecalMaterial;



public:
	// 팩토리 구조 : 어떤것을 스폰시킬때 내부적으로 처리해서 리턴시켜주는 방식
	// 공통적인 부분만 관리할 수 있기 때문에 외부에서 처리하는것보다 편함
	static AJG_Rifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	// 어떤 플랫폼이든(엑박이든 플스든 윈도우든 리눅스든) 인라인 함수 취급하라
	// 인라인은 함수를 호출하는 코드를 함수가 정의된 곳에다 생성하지 않고 컴파일러가 완전한 함수체를 함수가 호출되는 모든 장소에 삽입할 것을 요청하는 함수
	// 즉, 일반함수를 호출하면 해당 함수의 주소로 갔다가 계산하고 돌아오는 과정을 거쳐야하는데 inline 함수는 이미 치환되어있으므로 따로 함수 호출 과정을 통해서 주소를 이동할 필요없이 그 위치에서 처리하므로 속도가 빠름.
	// 언리얼은 인라인 함수를 사용할 것을 권장함
	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetEquipping() { return bEquipping; }
	FORCEINLINE bool GetAiming() { return bAiming; }

public:	
	// Sets default values for this actor's properties
	AJG_Rifle();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aiming();
	void End_Aiming();

	// 연사를 위해서 함수 3개 만듦
	void Begin_Fire();
	void Firing();
	void End_Fire();

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
