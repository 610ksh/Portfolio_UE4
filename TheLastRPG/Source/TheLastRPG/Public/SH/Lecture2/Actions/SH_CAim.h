#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "SH_CAim.generated.h"

UCLASS()
class THELASTRPG_API USH_CAim : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsAvailable() { return SpringArm != NULL && Camera != NULL; }
	FORCEINLINE bool IsZoom() { return bInZoom; }
	
public:
	USH_CAim();
	void BeginPlay(class ACharacter* InCharacter);

	void OnZoom();
	void OffZoom();

	void Tick(float DeltaTime);

private:
	UFUNCTION()
		void Zooming(float Output);

private:
	class UCurveFloat* Curve;

	class ASH_CHUD* HUD;

	class ACharacter* OwnerCharacter;
	class USH_CStateComponent* State;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bInZoom;

	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;
};
