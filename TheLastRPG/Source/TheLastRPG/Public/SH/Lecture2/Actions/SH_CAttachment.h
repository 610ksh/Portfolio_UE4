#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_CAttachment.generated.h"

UCLASS()
class THELASTRPG_API ASH_CAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

public:	
	ASH_CAttachment();

protected:
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
		class USH_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class USH_CStatusComponent* Status;
};
