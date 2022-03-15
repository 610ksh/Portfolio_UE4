#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightBeginOverlap); // void __(void) : ��������Ʈ �ڷ��� ����
DECLARE_DELEGATE(FBoxLightEndOverlap);
// �̱�ĳ��Ʈ, Return Ÿ�� �ְ�, 1���� �Ķ���� ���. (��ȯ�� Ÿ��, ���ϴ� ��������Ʈ Ÿ�� �̸�����, �Ű����� Ÿ��)
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