#pragma once

#include "CoreMinimal.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH_CDoAction_Warp.generated.h"

UCLASS()
class THELASTRPG_API ASH_CDoAction_Warp : public ASH_CDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoActin() override;

	virtual void Tick(float DeltaTime) override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator);

private:
	class UDecalComponent* Decal;
	FVector Location;
};
