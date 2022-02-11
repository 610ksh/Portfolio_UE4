// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JG_UserWidget_CrossHair.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API UJG_UserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnFocus();

	UFUNCTION(BlueprintImplementableEvent)
	void OffFocus();
};
