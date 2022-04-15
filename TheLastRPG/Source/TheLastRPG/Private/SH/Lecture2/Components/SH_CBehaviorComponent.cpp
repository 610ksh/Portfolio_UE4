#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/SH_Global.h"

#include "BehaviorTree/BlackboardComponent.h"

USH_CBehaviorComponent::USH_CBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USH_CBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool USH_CBehaviorComponent::IsWaitMode()
{
	return GetType() == ESH_BehaviorType::Wait;
}

bool USH_CBehaviorComponent::IsApproachMode()
{
	return GetType() == ESH_BehaviorType::Approach;
}

bool USH_CBehaviorComponent::IsActionMode()
{
	return GetType() == ESH_BehaviorType::Action;
}

bool USH_CBehaviorComponent::IsPatrolMode()
{
	return GetType() == ESH_BehaviorType::Patrol;
}

bool USH_CBehaviorComponent::IsHittedMode()
{
	return GetType() == ESH_BehaviorType::Hitted;
}

bool USH_CBehaviorComponent::IsAvoidMode()
{
	return GetType() == ESH_BehaviorType::Avoid;
}

void USH_CBehaviorComponent::SetWaitMode()
{
	ChangeType(ESH_BehaviorType::Wait);
}

void USH_CBehaviorComponent::SetApproachMode()
{
	ChangeType(ESH_BehaviorType::Approach);
}

void USH_CBehaviorComponent::SetActionMode()
{
	ChangeType(ESH_BehaviorType::Action);
}

void USH_CBehaviorComponent::SetPatrolMode()
{
	ChangeType(ESH_BehaviorType::Patrol);
}

void USH_CBehaviorComponent::SetHittedMode()
{
	ChangeType(ESH_BehaviorType::Hitted);
}

void USH_CBehaviorComponent::SetAvoidMode()
{
	ChangeType(ESH_BehaviorType::Avoid);
}

void USH_CBehaviorComponent::ChangeType(ESH_BehaviorType InType)
{
	ESH_BehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

ASH_CActionPlayer * USH_CBehaviorComponent::GetTargetPlayer()
{
	return Cast<ASH_CActionPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector USH_CBehaviorComponent::GetWarpLocation()
{
	return Blackboard->GetValueAsVector(WarpKey);
}

ESH_BehaviorType USH_CBehaviorComponent::GetType()
{
	return (ESH_BehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}