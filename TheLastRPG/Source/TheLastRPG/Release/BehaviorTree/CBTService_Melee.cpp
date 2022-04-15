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


	/// 맞았냐
	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	/// 탐지여부
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

		/// 대상이 죽었다면
		if (targetState->IsDeadMode())
		{
			behavior->SetWaitMode();
			return;
		}
	}

	/// 안죽었고 공격 범위안에 들어왔다면 : 공격
	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetMeleeActionRange())
	{
		behavior->SetActionMode();
		return;
	}
	
	/// 공격 범위 밖이고, 시야 범위 안이라면 : 쫓아감
	if (distance < controller->GetSightRadius())
	{
		behavior->SetApproachMode();
		return;
	}

}