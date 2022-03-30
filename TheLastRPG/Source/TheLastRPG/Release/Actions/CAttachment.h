#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class THELASTRPG_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

};