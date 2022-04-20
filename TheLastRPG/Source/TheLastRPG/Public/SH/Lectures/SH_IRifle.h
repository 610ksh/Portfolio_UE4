#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SH_IRifle.generated.h"

UINTERFACE(MinimalAPI)
class USH_IRifle : public UInterface
{
	GENERATED_BODY()
};

/*
	1. Player가 상속함
*/
class THELASTRPG_API ISH_IRifle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class ASH_CRifle* GetRifle() = 0;
	virtual void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) = 0;
	virtual void OnFocus() = 0;
	virtual void OffFocus() = 0;
};