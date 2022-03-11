#include "SH/Lecture2/BehaviorTree/SH_CBTService_Melee.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CPatrolComponent.h"
#include "SH/SH_Global.h"

USH_CBTService_Melee::USH_CBTService_Melee()
{
	NodeName = "Melee";
}

void USH_CBTService_Melee::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASH_CAIController* controller = Cast<ASH_CAIController>(OwnerComp.GetOwner());
	USH_CBehaviorComponent* behavior = SH_CHelpers::GetComponent<USH_CBehaviorComponent>(controller);

	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(ai);
	USH_CPatrolComponent* patrol = SH_CHelpers::GetComponent<USH_CPatrolComponent>(ai);

	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	ASH_CActionPlayer* target = behavior->GetTargetPlayer();
	if (target == NULL)
	{
		// TODO 패트롤 모드
		if (patrol != NULL && patrol->IsValid())
		{
			behavior->SetPatrolMode();
			return;
		}

		behavior->SetWaitMode();
		return;
	}
	else
	{
		USH_CStateComponent* targetState = SH_CHelpers::GetComponent< USH_CStateComponent>(target);
		if (targetState->IsDeadMode())
		{
			behavior->SetWaitMode();
			return;
		}
	}

	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetBehaviorRange())
	{
		behavior->SetActionMode();
		return;
	}

	if (distance < controller->GetSightRadius())
	{
		behavior->SetApproachMode();
		return;
	}

}
