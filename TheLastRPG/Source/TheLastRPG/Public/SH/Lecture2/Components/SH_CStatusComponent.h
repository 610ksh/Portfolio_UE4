#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESH_CharacterSpeed : uint8
{
	Walk, Run, Sprint, Max,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API USH_CStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float Speed[(int32)ESH_CharacterSpeed::Max] = { 200,400,600 };

public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESH_CharacterSpeed::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESH_CharacterSpeed::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESH_CharacterSpeed::Sprint]; }

	FORCEINLINE bool CanMove() { return bCanMove; }

public:
	USH_CStatusComponent();

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);

	void SetMove();
	void SetStop();

	void SetSpeed(ESH_CharacterSpeed InType);

protected:
	virtual void BeginPlay() override;

private:
	bool bCanMove = true;

	float Health;
};
