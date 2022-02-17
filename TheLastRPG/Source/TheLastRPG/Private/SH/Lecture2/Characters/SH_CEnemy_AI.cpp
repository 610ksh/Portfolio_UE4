#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CPatrolComponent.h"
#include "SH/SH_Global.h"

ASH_CEnemy_AI::ASH_CEnemy_AI()
{
	SH_CHelpers::CreateActorComponent<USH_CPatrolComponent>(this, &Patrol, "Patrol");
}