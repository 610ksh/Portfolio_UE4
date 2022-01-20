// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG08_EventTrigger.generated.h"

// �̺�Ʈ�� �̱��� ����
UCLASS()
class THELASTRPG_API AJG08_EventTrigger : public AActor
{
	GENERATED_BODY()

public: // �̺�Ʈ�� ���ο��� �Ͼ�� ������ Ŭ���� �ȿ� ����
	DECLARE_EVENT_OneParam(ASH_EventTrigger, FEventTrigger, int32);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:
	// Sets default values for this actor's properties
	AJG08_EventTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FEventTrigger OnEventTrigger;

};
