#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SH_CBTTaskNode_Patrol.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	USH_CBTTaskNode_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
