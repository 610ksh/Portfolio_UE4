#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Light.generated.h"

UCLASS()
class THELASTRPG_API ASH_Light : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light2;

public:	
	ASH_Light();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight();
	UFUNCTION()
		void OffLight();

	UFUNCTION()
		FString OnRandomLight(FLinearColor InColor);
};
