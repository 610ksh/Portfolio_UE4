// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG/130_/Actions/JG_CActionData.h"
#include "JG_CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate_JG);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate_JG);

UCLASS()
class THELASTRPG_API AJG_CEquipment : public AActor
{
	GENERATED_BODY()

	public:
	FORCEINLINE void SetData(FEquipmentData_JG InData) { Data = InData; }
	//FORCEINLINE void SetColor(FLinearColor_JG InColor) { Color = InColor; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }
	
public:
	AJG_CEquipment();

public:
	//// 장착 명령
	UFUNCTION(BlueprintNativeEvent)
	void Equip();
	void Equip_Implementation();

	// 장착 개시
	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	// 장착 완료
	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();


	// 해제 명령
	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FEquipmentDelegate_JG OnEquipmentDelegate;

	UPROPERTY(BlueprintAssignable)
	FUnequipmentDelegate_JG OnUnequipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UJG_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UJG_CStatusComponent* Status;

private:
	bool bEquipped;
	FEquipmentData_JG Data;
};
