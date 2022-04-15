#include "Release/BehaviorTree/CBTService_Melee.h"
#include "Release/AI/CAIController.h"
#include "Release/AI/CEnemy_AI.h"
#include "Release/AI/CBehaviorComponent.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Global.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = Helpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = Helpers::GetComponent<UCStateComponent>(ai);


	/// �¾ҳ�
	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	/// Ž������
	ACharacter* target = behavior->GetTargetPlayer();
	if (target == NULL)
	{
		// TODO : patrol

		behavior->SetWaitMode();
		return;
	}
	else
	{
		UCStateComponent* targetState = Helpers::GetComponent<UCStateComponent>(target);

		/// ����� �׾��ٸ�
		if (targetState->IsDeadMode())
		{
			behavior->SetWaitMode();
			return;
		}
	}

	/// ���׾��� ���� �����ȿ� ���Դٸ� : ����
	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetMeleeActionRange())
	{
		behavior->SetActionMode();
		return;
	}
	
	/// ���� ���� ���̰�, �þ� ���� ���̶�� : �Ѿư�
	if (distance < controller->GetSightRadius())
	{
		behavior->SetApproachMode();
		return;
	}

}