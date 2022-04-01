#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Release/Actions/CAction.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate);

UCLASS()
class THELASTRPG_API ACEquipment : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetEquipData(const FEquipmentData& InData) { EquipData = InData; }
	FORCEINLINE void SetUnequipData(const FEquipmentData& InData) { UnequipData = InData; }

public:
	ACEquipment();

public:
	/// Equip
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	/// Unequip
	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Unequip();
	void Begin_Unequip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Unequip();
	void End_Unequip_Implementation();


protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FEquipmentDelegate OnEquipmentDelegate;
	UPROPERTY(BlueprintAssignable)
		FUnequipmentDelegate OnUnequipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

private:
	FEquipmentData EquipData;
	FEquipmentData UnequipData;
};