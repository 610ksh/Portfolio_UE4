#pragma once

#include "CoreMinimal.h"
#include "Release/Actions/CDoAction.h"
#include "CDoAction_Throw.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction_Throw : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void OnAim() override;
	virtual void OffAim() override;

protected:
	virtual void BeginPlay() override;

private:
	class UCAim* Aim;
};
