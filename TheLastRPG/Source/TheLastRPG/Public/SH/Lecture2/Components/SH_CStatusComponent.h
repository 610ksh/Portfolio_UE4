#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float WalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float RunSpeed = 400.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float SprintSpeed = 600.0f;

public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

	FORCEINLINE bool CanMove() { return bCanMove; }

public:	
	USH_CStatusComponent();

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);

	void SetMove();
	void SetStop();

protected:
	virtual void BeginPlay() override;

private:
	bool bCanMove = true;

	float Health;
};
