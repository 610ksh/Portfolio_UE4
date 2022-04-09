#pragma once

#include "CoreMinimal.h"
#include "Release/Actions/CDoAction.h"
#include "CDoAction_FireStorm.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction_FireStorm : public ACDoAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Time = 5.0f;
	UPROPERTY(EditAnywhere)
		float Distance = 200.0f;
	UPROPERTY(EditAnywhere)
		float Speed = 100.0f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void Finish();

private:
	class UBoxComponent* Box;
	class UParticleSystemComponent* Attached;
	float Angle;
};
