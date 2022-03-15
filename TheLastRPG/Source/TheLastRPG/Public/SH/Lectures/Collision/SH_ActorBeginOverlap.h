#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_ActorBeginOverlap.generated.h"

UCLASS()
class THELASTRPG_API ASH_ActorBeginOverlap : public AActor
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
	ASH_ActorBeginOverlap();

protected:
	virtual void BeginPlay() override;

public:
	// AActor*, OverlappedActor, AActor*, OtherActor
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	//  AActor*, OverlappedActor, AActor*, OtherActor 
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
