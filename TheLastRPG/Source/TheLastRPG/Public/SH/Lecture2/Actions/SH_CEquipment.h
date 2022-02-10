#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH_CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate);

UCLASS()
class THELASTRPG_API ASH_CEquipment : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetData(FEquipmentData InData) { Data = InData; }
	FORCEINLINE void SetColor(FLinearColor InColor) { Color = InColor; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }
	
public:	
	ASH_CEquipment();

public:
	// 장착 명령
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
		FEquipmentDelegate OnEquipmentDelegate;

	UPROPERTY(BlueprintAssignable)
		FUnequipmentDelegate OnUnequipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class USH_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class USH_CStatusComponent* Status;

private:
	bool bEquipped;
	FEquipmentData Data; // for ActionData class
	FLinearColor Color;
};
