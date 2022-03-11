#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_CPatrolPath.generated.h"

UCLASS()
class THELASTRPG_API ASH_CPatrolPath : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Loop")
		bool bLoop;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }

public:	
	ASH_CPatrolPath();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

};
