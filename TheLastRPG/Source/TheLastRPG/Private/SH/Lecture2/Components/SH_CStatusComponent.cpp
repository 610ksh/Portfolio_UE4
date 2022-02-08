#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

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