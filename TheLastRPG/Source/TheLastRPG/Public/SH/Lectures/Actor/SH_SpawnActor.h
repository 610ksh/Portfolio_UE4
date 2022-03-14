#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_SpawnActor.generated.h"

UCLASS()
class THELASTRPG_API ASH_SpawnActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	ASH_SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor();

private:
	class UMaterialInstanceDynamic* Material;

};
