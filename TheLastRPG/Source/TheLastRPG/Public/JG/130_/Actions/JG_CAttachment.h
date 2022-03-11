// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_CAttachment.generated.h"

UCLASS()
class THELASTRPG_API AJG_CAttachment : public AActor
{
	GENERATED_BODY()
	
	protected:
	UFUNCTION(BlueprintCallable)
	void AttachTo(FName InSocketName);
	
public:	
	// Sets default values for this actor's properties
	AJG_CAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip();

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	class UJG_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
	class UJG_CStatusComponent* Status;
};
