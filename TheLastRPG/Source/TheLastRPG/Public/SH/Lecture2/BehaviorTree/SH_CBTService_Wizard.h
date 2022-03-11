#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SH_CBTService_Wizard.generated.h"

UCLASS()
class THELASTRPG_API USH_CBTService_Wizard : public UBTService
{
	GENERATED_BODY()
	
public:
	USH_CBTService_Wizard();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
