// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YH_C10_Override.generated.h"

UCLASS()
class THELASTRPG_API AYH_C10_Override : public AActor
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
	AYH_C10_Override();

protected:
	virtual void BeginPlay() override;

protected:
	//�Ѵ� �ڽĿ��� �����ϴ�(����)
	//���� ���ִµ� �˾Ƽ� ��ü�� ���弼��
	UFUNCTION(BlueprintImplementableEvent)
		void ChangeColorRed();
	//�⺻���δ� �̷��� �����؇J�µ� �ʿ��ϸ� ������ �ض�.
	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();
	void ChangeColorWhite_Implementation(); //������ �Ҷ��� implement�� ���δ�.


private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
