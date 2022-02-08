#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_CUserWidget_Health.generated.h"

UCLASS()
class THELASTRPG_API USH_CUserWidget_Health : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float Health, float MaxHealth);
};
