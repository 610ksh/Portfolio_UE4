#pragma once

#include "CoreMinimal.h"
#include "Release/Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnableCombo = true; }
	FORCEINLINE void DisableCombo() { bEnableCombo = false; }

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

	virtual void OnAttachmentCollision();
	virtual void OffAttachmentCollision();

private:
	UFUNCTION()
		void RestoreDilation();

private:
	bool bExistCombo;
	bool bEnableCombo;
	bool bLastCombo;

	int32 ComboIndex;
	TArray<class ACharacter*> HittedCharacters;
};