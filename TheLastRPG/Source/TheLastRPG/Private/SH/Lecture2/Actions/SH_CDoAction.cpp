#include "SH/Lecture2/Actions/SH_CDoAction.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

ASH_CDoAction::ASH_CDoAction()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASH_CDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = SH_CHelpers::GetComponent<USH_CStateComponent>(OwnerCharacter);
	Status = SH_CHelpers::GetComponent<USH_CStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ASH_CDoAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}