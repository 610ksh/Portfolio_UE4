#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Box.generated.h"

UCLASS()
class THELASTRPG_API ASH_Box : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh[3];

public:
	ASH_Box();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnPhysics(int32 InIndex, FLinearColor InColor);
	UFUNCTION()
		void OffPhysics();

private:
	UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocation[3];
};