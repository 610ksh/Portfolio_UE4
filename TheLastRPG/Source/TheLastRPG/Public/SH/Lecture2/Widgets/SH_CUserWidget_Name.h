#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_CUserWidget_Name.generated.h"

UCLASS()
class THELASTRPG_API USH_CUserWidget_Name : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetNameText(const FString& InName);
};
