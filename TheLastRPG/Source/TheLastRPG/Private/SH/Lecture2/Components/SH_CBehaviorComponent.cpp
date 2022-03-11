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
	return GetType() == EBehaviorType::Wait;
}

bool USH_CBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool USH_CBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool USH_CBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool USH_CBehaviorComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

bool USH_CBehaviorComponent::IsAvoidMode()
{
	return GetType() == EBehaviorType::Avoid;
}

void USH_CBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void USH_CBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void USH_CBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void USH_CBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void USH_CBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

void USH_CBehaviorComponent::SetAvoidMode()
{
	ChangeType(EBehaviorType::Avoid);
}

void USH_CBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
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

EBehaviorType USH_CBehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}