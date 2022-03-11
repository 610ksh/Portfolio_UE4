#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH_CBTTaskNode_SetSpeed.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTTaskNode_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		ECharacterSpeed SpeedType;

public:
	USH_CBTTaskNode_SetSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
