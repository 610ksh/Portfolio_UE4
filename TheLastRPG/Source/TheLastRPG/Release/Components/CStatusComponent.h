#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float WalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float RunSpeed = 400.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float SprintSpeed = 600.0f;

public:
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

	FORCEINLINE bool CanMove() { return bCanMove; }

public:	
	UCStatusComponent();

	void SetMove();
	void SetStop();

protected:
	virtual void BeginPlay() override;
	
private:
	bool bCanMove = true;
};