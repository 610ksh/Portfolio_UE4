#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightBeginOverlap); // void __(void) : 델리게이트 자료형 선언
DECLARE_DELEGATE(FBoxLightEndOverlap);
// 싱글캐스트, Return 타입 있고, 1개의 파라미터 사용. (반환형 타입, 원하는 델리게이트 타입 이름지정, 매개변수 타입)
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
	ASH_Trigger();

protected:
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