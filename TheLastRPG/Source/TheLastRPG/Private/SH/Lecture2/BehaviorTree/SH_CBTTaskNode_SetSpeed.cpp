#include "SH/Lecture2/BehaviorTree/SH_CBTTaskNode_SetSpeed.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/SH_Global.h"

USH_CBTTaskNode_SetSpeed::USH_CBTTaskNode_SetSpeed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type USH_CBTTaskNode_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASH_CAIController* controller = Cast< ASH_CAIController>(OwnerComp.GetOwner());
	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(controller->GetPawn());
	USH_CStatusComponent* status = SH_CHelpers::GetComponent<USH_CStatusComponent>(ai);

	status->SetSpeed(SpeedType);
	return EBTNodeResult::Succeeded;
}