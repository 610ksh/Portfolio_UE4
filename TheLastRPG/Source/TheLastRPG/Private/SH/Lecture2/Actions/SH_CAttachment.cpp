#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ASH_CAttachment::ASH_CAttachment()
{

}

void ASH_CAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = SH_CHelpers::GetComponent<USH_CStateComponent>(OwnerCharacter);
	Status = SH_CHelpers::GetComponent<USH_CStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ASH_CAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}