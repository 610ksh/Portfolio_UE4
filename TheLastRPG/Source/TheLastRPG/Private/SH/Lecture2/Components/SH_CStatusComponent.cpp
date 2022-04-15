#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/CharacterMovementComponent.h"

USH_CStatusComponent::USH_CStatusComponent()
{

}

void USH_CStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void USH_CStatusComponent::SetMove()
{
	bCanMove = true;
}

void USH_CStatusComponent::SetStop()
{
	bCanMove = false;
}

void USH_CStatusComponent::SetSpeed(ESH_CharacterSpeed InType)
{
	UCharacterMovementComponent* movement = SH_CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	movement->MaxWalkSpeed = Speed[(int32)InType];
}

void USH_CStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void USH_CStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}