#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h" // EDrawDebugTrace::Type
#include "SH_CFeetComponent.generated.h"

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance; // X축만 이용
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance; // X축만 이용
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance; // Z축만 이용

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation; // Z축만 이용
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation; // Z축만 이용
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API USH_CFeetComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName LeftSocket = "foot_l";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName RightSocket = "foot_r";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float TraceDistance = 55.0f; // 추적할 최대 거리
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float InterpSpeed = 17.0f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float OffsetDistance = 5.0f;

public:
	FORCEINLINE const FFeetData& GetData() { return Data; }

public:
	USH_CFeetComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Trace(FName InSocket, float& OutDistance, FRotator& OutRotation);

private:
	class ACharacter* OwnerCharacter;

	FFeetData Data;
};
