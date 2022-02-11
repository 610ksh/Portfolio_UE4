#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_SweepTrigger.generated.h"

UCLASS()
class THELASTRPG_API ASH_SweepTrigger : public AActor
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
	ASH_SweepTrigger();

protected:
	virtual void BeginPlay() override;

};
