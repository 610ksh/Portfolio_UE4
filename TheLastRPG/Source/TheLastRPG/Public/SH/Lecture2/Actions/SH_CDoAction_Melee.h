#pragma once

#include "CoreMinimal.h"
#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH_CDoAction_Melee.generated.h"

UCLASS()
class THELASTRPG_API ASH_CDoAction_Melee : public ASH_CDoAction
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoActin() override;

public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	
	virtual void OnAttachmentCollision() override;
	virtual void OffAttachmentCollision() override;

private:
	bool bExist; // �޺� ���࿩��
	bool bEnable; // �޺� �Է� ����
	bool bLast; // ������ �޺�����

	int32 Index; // ���� �޺� �ִϸ��̼� �ε���

	TArray<class ACharacter*> HittedCharacters;
};
