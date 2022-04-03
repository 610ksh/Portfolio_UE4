#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIEnemy : public UInterface
{
	GENERATED_BODY()
};

class THELASTRPG_API IIEnemy
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;

};