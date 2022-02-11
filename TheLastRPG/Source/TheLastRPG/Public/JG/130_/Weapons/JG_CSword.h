// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_CSword.generated.h"

UCLASS()
class THELASTRPG_API AJG_CSword : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "OneHandSword")
	class USkeletalMeshComponent* Mesh;


	UPROPERTY(VisibleDefaultsOnly, Category = "OneHandSword")
	FName HandSocket = "Hand_Sword";

	UPROPERTY(VisibleDefaultsOnly, Category = "OneHandSword")
	FName HolsterSocket = "Holster_Sword";

	UPROPERTY(VisibleDefaultsOnly, Category = "OneHandSword")
	class UAnimMontage* GrabMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "OneHandSword")
	class UAnimMontage* UngrabMontage;


public:
	static AJG_CSword* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:	
	// Sets default values for this actor's properties
	AJG_CSword();

//public:
//	FORCEINLINE bool GetEquipped() { return bEquipped; }
//	void Equip();
//	void Begin_Equip();
//	void End_Equip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;


};
