// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG10_Override.generated.h"

UCLASS()
class THELASTRPG_API AJG10_Override : public AActor
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
	AJG10_Override();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	// �˾Ƽ� ��ü ������. ���� �س���.
	UFUNCTION(BlueprintImplementableEvent) 
	void ChangeColorRed();

	// �츮�� �⺻�� ����� ����. ������ �ҰŸ� �˾Ƽ� �ض�.
	UFUNCTION(BlueprintNativeEvent) 
	void ChangeColorWhite();
	void ChangeColorWhite_Implementation(); //C���� �ڽ� ������ �� �� _Implementation����

private:
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
