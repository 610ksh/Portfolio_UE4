#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_EventTrigger.generated.h"

UCLASS()
class THELASTRPG_API ASH_EventTrigger : public AActor
{
	GENERATED_BODY()

public: // 이벤트는 델리게이트와 다르게 클래스 내부에서 선언한다!
	DECLARE_EVENT_OneParam(ASH_EventTrigger, FEventTrigger, int32);
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	ASH_EventTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FEventTrigger OnEventTrigger;
};
