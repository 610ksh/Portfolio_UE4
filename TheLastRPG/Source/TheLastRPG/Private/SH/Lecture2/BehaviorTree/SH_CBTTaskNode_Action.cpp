#include "SH/Lecture2/BehaviorTree/SH_CBTTaskNode_Action.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/SH_Global.h"

USH_CBTTaskNode_Action::USH_CBTTaskNode_Action()
{
	bNotifyTick = true;
	NodeName = "Action";
}

EBTNodeResult::Type USH_CBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASH_CAIController* controller = Cast< ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(ai);

	TotalTime = 0.0f;
	action->DoAction();

	return EBTNodeResult::InProgress;
}

void USH_CBTTaskNode_Action::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	ASH_CAIController* controller = Cast< ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(ai);

	TotalTime += DeltaSeconds;

	if (state->IsIdleMode() && TotalTime > Delay)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
