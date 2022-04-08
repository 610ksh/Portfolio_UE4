#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);

UCLASS()
class THELASTRPG_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Scene;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);
	UFUNCTION(BlueprintCallable)
		void AttachToCollision(class UShapeComponent* InComponent, FName InSocketName);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	ACAttachment();

	void OnCollision();
	void OffCollision();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	UPROPERTY(BlueprintAssignable)
		FAttachmentEndOverlap OnAttachmentEndOverlap;

	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OnAttachmentCollision;
	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OffAttachmentCollision;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;
	
private:
	TArray<class UShapeComponent*> ShapeComponents;

};