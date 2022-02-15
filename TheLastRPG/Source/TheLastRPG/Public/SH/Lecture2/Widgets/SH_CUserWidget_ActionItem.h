#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_CUserWidget_ActionItem.generated.h"

UCLASS()
class THELASTRPG_API USH_CUserWidget_ActionItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
		void Click();
	UFUNCTION(BlueprintCallable)
		void Hover();
	UFUNCTION(BlueprintCallable)
		void Unhover();

private:
	class USH_CUserWidget_ActionList* GetActionList();
};
