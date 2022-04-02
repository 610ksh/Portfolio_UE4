#include "Release/Actions/CDoAction.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

ACDoAction::ACDoAction()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Helpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = Helpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ACDoAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}