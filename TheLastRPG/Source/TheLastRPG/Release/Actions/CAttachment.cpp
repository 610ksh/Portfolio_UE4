#include "Release/Actions/CAttachment.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Components/CStatusComponent.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

ACAttachment::ACAttachment()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Helpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = Helpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}