#include "SH/Lecture2/BehaviorTree/SH_CEnvQueryContext_Player.h"
#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/SH_Global.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USH_CEnvQueryContext_Player::ProvideContext(FEnvQueryInstance & QueryInstance, FEnvQueryContextData & ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ASH_CEnemy_AI* ai = Cast<ASH_CEnemy_AI>(QueryInstance.Owner.Get());
	USH_CBehaviorComponent* behavior = SH_CHelpers::GetComponent<USH_CBehaviorComponent>(ai->GetController());

	if (!!behavior->GetTargetPlayer())
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, behavior->GetTargetPlayer());
}
