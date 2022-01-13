// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YH_C01_ActorBeginOverlap.generated.h"

UCLASS()
class THELASTRPG_API AYH_C01_ActorBeginOverlap : public AActor
{
	GENERATED_BODY()
	
private:
	//�ָ� �θ�� ���ڴ�.
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	//�浹ü ����
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	//�ؽ�Ʈ�������Ҿ�
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	

	AYH_C01_ActorBeginOverlap();

protected:

	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


};
