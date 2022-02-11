#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SH_ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USH_ICharacter : public UInterface
{
	GENERATED_BODY()
};

class THELASTRPG_API ISH_ICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
};
