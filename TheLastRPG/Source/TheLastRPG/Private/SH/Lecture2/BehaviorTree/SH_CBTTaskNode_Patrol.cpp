#include "SH/Lecture2/BehaviorTree/SH_CBTTaskNode_Patrol.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CPatrolComponent.h"

#include "SH/SH_Global.h"

USH_CBTTaskNode_Patrol::USH_CBTTaskNode_Patrol()
{
	bNotifyTick = true;
	NodeName = "Patrol";
}

EBTNodeResult::Type USH_CBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASH_CAIController* controller = Cast< ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CPatrolComponent* patrol = SH_CHelpers::GetComponent<USH_CPatrolComponent>(ai);

	FVector location;
	float acceptance;

	if (patrol->GetMoveTo(location, acceptance) == false)
		return EBTNodeResult::Failed;


	return EBTNodeResult::InProgress;
}

void USH_CBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASH_CAIController* controller = Cast< ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CPatrolComponent* patrol = SH_CHelpers::GetComponent<USH_CPatrolComponent>(ai);

	FVector location;
	float acceptance;

	patrol->GetMoveTo(location, acceptance);
	EPathFollowingRequestResult::Type type = controller->MoveToLocation(location, acceptance, false);

	if (type == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (type == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		patrol->UpdateNextIndex();
	}
}

