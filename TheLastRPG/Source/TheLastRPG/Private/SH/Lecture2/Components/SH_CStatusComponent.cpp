#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

USH_CStatusComponent::USH_CStatusComponent()
{

}



void USH_CStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USH_CStatusComponent::SetMove()
{
	bCanMove = true;
}

void USH_CStatusComponent::SetStop()
{
	bCanMove = false;
}
