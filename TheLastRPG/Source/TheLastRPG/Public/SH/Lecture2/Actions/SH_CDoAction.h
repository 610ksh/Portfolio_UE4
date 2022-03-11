#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH/Lecture2/Actions/SH_CActionData.h" // for FDoActionData
#include "SH_CDoAction.generated.h"

UCLASS()
class THELASTRPG_API ASH_CDoAction : public AActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }

public:	
	ASH_CDoAction();

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoActin() {}

	virtual void OnAim() {}
	virtual void OffAim() {}
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	
	UFUNCTION()
		virtual void OnAttachmentCollision() {}
	UFUNCTION()
		virtual void OffAttachmentCollision(){}

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class USH_CStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class USH_CStatusComponent* Status;

protected:
	const bool* bEquipped;
	TArray<FDoActionData> Datas;

};
