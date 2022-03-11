#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH_CBTTaskNode_Change.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTTaskNode_Change : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		EActionType Type;

public:
	USH_CBTTaskNode_Change();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
