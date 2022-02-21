#include "SH/Lecture2/BehaviorTree/SH_CBTService_Wizard.h"

#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/SH_Global.h"

USH_CBTService_Wizard::USH_CBTService_Wizard()
{
	NodeName = "Wizard";
}

void USH_CBTService_Wizard::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASH_CAIController* controller = Cast<ASH_CAIController>(OwnerComp.GetOwner());
	USH_CBehaviorComponent* behavior = SH_CHelpers::GetComponent<USH_CBehaviorComponent>(controller);

	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(ai);

	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	ASH_CActionPlayer* target = behavior->GetTargetPlayer();
	if (target == NULL)
	{
		behavior->SetWaitMode();
		controller->ClearFocus(EAIFocusPriority::Default);
		return;
	}
	else // �����̺� ���� �÷��̾ �߰ߵƴٸ�
	{
		USH_CStateComponent* targetState = SH_CHelpers::GetComponent< USH_CStateComponent>(target);
		if (targetState->IsDeadMode()) // �÷��̾ �׾��ٸ�
		{
			behavior->SetWaitMode(); // �ٽ� Wait ����
			return;
		}
	}

	controller->SetFocus(target); // Ÿ���� ���غ���

	float action = controller->GetSightRadius();
	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetBehaviorRange())
	{
		behavior->SetAvoidMode();
		return;
	}

	if (distance < action)
	{
		behavior->SetActionMode();
		return;
	}
}