#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SH_CBTTaskNode_Action.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTTaskNode_Action : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Delay = 2.0f; // 공격후 딜레이 넣어주는것. 텀 주는것

public:
	USH_CBTTaskNode_Action();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	float TotalTime = 0.0f;
};
