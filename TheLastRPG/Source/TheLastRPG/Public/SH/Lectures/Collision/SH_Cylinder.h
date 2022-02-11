#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Cylinder.generated.h"

UCLASS()
class THELASTRPG_API ASH_Cylinder : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	
public:	
	ASH_Cylinder();

protected:
	virtual void BeginPlay() override;

};
