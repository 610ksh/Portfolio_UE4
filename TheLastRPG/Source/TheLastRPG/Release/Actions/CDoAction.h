#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Release/Actions/CAction.h"
#include "CDoAction.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetAttackDatas(const TArray<FDoActionData>& InDatas) { AttackDatas = InDatas; }
	FORCEINLINE void SetSkillDatas(const TArray<FDoActionData>& InDatas) { SkillDatas = InDatas; }
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }

public:
	ACDoAction();

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION() // class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentCollision() {}
	UFUNCTION()
		virtual void OffAttachmentCollision() {}

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

protected:
	const bool* bEquipped;
	TArray<FDoActionData> AttackDatas;
	TArray<FDoActionData> SkillDatas;
};
