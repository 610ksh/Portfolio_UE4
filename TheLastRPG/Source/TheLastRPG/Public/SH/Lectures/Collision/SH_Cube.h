#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Cube.generated.h"

UCLASS()
class THELASTRPG_API ASH_Cube : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
public:	
	ASH_Cube();

protected:
	virtual void BeginPlay() override;

};
