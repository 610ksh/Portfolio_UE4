#include "SH/Lecture2/BehaviorTree/SH_CBTTaskNode_Change.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/SH_Global.h"

USH_CBTTaskNode_Change::USH_CBTTaskNode_Change()
{
	bNotifyTick = true;
	NodeName = "Change";
}

EBTNodeResult::Type USH_CBTTaskNode_Change::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASH_CAIController* controller = Cast<ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(ai);

	if (Type == EActionType::Warp)
	{
		if (action->IsWarpMode() == false)
			action->SetWarpMode();
	}
	else if (Type == EActionType::IceBall)
	{
		if (action->IsIceBallMode() == false)
			action->SetIceBallMode();
	}

	return EBTNodeResult::InProgress;
}

void USH_CBTTaskNode_Change::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASH_CAIController* controller = Cast<ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(ai);

	if (state->IsIdleMode())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

