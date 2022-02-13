#pragma once

#include "CoreMinimal.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH_CDoAction_FireStorm.generated.h"

UCLASS()
class THELASTRPG_API ASH_CDoAction_FireStorm : public ASH_CDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoActin() override;

};
