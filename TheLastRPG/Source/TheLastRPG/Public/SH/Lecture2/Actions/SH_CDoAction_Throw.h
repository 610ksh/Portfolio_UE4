#pragma once

#include "CoreMinimal.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH_CDoAction_Throw.generated.h"

UCLASS()
class THELASTRPG_API ASH_CDoAction_Throw : public ASH_CDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoActin() override;

	virtual void OnAim() override;
	virtual void OffAim() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnThrowBeginOverlap(FHitResult InHitResult);

private:
	class USH_CAim* Aim;
};
