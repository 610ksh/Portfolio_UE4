#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

UCStatusComponent::UCStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}