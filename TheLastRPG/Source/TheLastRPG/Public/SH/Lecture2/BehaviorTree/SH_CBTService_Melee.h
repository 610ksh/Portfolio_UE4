#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SH_CBTService_Melee.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTService_Melee : public UBTService
{
	GENERATED_BODY()
	
public:
	USH_CBTService_Melee();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
