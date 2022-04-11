#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h" // added FTimeline
#include "CAim.generated.h"

UCLASS()
class THELASTRPG_API UCAim : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsAvailable() { return SpringArm != NULL && Camera != NULL; }
	FORCEINLINE bool IsZoom() { return bInZoom; }

public:
	UCAim();
	void BeginPlay(class ACharacter* InCharacter);
	void Tick(float DeltaTime);

	void OnZoom();
	void OffZoom();

private:
	UFUNCTION()
		void Zooming(float Output);

private:
	class UCStateComponent* State;

	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;
	class UCurveFloat* Curve;

	bool bInZoom;
	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;
};
