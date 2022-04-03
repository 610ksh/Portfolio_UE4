#pragma once

#include "CoreMinimal.h"
#include "Release/Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void EnableCombo() { bEnableCombo = true; }
	FORCEINLINE void DisableCombo() { bEnableCombo = false; }

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

private:
	bool bExistCombo;
	bool bEnableCombo;
	bool bLastCombo;

	int32 comboIndex;
};