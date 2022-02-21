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
	else // 비헤이비어를 통해 플레이어가 발견됐다면
	{
		USH_CStateComponent* targetState = SH_CHelpers::GetComponent< USH_CStateComponent>(target);
		if (targetState->IsDeadMode()) // 플레이어가 죽었다면
		{
			behavior->SetWaitMode(); // 다시 Wait 모드로
			return;
		}
	}

	controller->SetFocus(target); // 타깃을 향해본다

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