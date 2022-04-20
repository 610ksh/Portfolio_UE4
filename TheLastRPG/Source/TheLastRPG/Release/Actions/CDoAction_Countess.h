#pragma once

#include "CoreMinimal.h"
#include "Release/Actions/CDoAction_Melee.h"
#include "CDoAction_Countess.generated.h"

UCLASS()
class THELASTRPG_API ACDoAction_Countess : public ACDoAction_Melee
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float CollisionRadius = 200.0f;

	UPROPERTY(EditAnywhere)
		FTransform HitEffectOffset;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* HitParticle;

public:
	ACDoAction_Countess();

	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void DoSkill_Q() override;
	virtual void Begin_Skill_Q() override;
	virtual void End_Skill_Q() override;

	virtual void DoSkill_E() override;
	virtual void End_Skill_E() override;
	virtual void Begin_Skill_E() override;

	virtual void DoSkill_R() override;
	virtual void Begin_Skill_R() override;
	virtual void End_Skill_R() override;

	virtual void DoSkill_F() override;
	virtual void End_Skill_F() override;
	virtual void Begin_Skill_F() override;

public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

	virtual void OnAttachmentCollision();
	virtual void OffAttachmentCollision();

private:
	class UParticleSystemComponent* Attached;

};
