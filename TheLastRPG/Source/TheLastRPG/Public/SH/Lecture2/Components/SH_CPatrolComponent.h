#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_CPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTRPG_API USH_CPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class ASH_CPatrolPath* Path;
	UPROPERTY(EditAnywhere)
		int32 Index;
	UPROPERTY(EditAnywhere)
		bool bReverse;
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 50.0f;

public:
	FORCEINLINE bool IsValid() { return Path != NULL; } 

public:	
	USH_CPatrolComponent();

	bool GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius);
	void UpdateNextIndex();

protected:
	virtual void BeginPlay() override;

};
