#include "Release/BehaviorTree/CBTTaskNode_SetSpeed.h"
#include "Release/AI/CAIController.h"
#include "Release/AI/CEnemy_AI.h"
#include "Release/AI/CBehaviorComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

UCBTTaskNode_SetSpeed::UCBTTaskNode_SetSpeed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = Helpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStatusComponent* status = Helpers::GetComponent<UCStatusComponent>(ai);

	status->SetSpeed(SpeedType);

	return EBTNodeResult::Succeeded;
}