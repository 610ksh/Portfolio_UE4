#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_COptionActorComponent.generated.h"


UCLASS(ClassGroup = (GameProject), meta = (BlueprintSpawnableComponent))
class THELASTRPG_API USH_COptionActorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float HorizontalLookRate = 60;
	UPROPERTY(EditDefaultsOnly)
		float VerticalLookRate = 45;

public:
	FORCEINLINE float GetHorizontalLookRate() { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() { return VerticalLookRate; }

public:
	USH_COptionActorComponent();

protected:
	virtual void BeginPlay() override;

};
