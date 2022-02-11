// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightBeginOverlap); // void __(void) : 델리게이트 자료형 선언
DECLARE_DELEGATE(FBoxLightEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor);

UCLASS()
class THELASTRPG_API ASH_Trigger : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	// Sets default values for this actor's properties
	ASH_Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// AActor*, OverlappedActor, AActor*, OtherActor
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	//  AActor*, OverlappedActor, AActor*, OtherActor 
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap OnBoxLightRandomBeginOverlap;
};