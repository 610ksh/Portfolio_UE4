#pragma once

#include "CoreMinimal.h"
#include "SH/Lecture2/Characters/SH_CEnemy.h"
#include "SH_CEnemy_AI.generated.h"

UCLASS()
class THELASTRPG_API ASH_CEnemy_AI : public ASH_CEnemy
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CPatrolComponent* Patrol;

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

public:
	ASH_CEnemy_AI();

};
