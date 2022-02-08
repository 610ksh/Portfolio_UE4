#include "SH/Lecture2/Actions/SH_CAttachment.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ShapeComponent.h"

ASH_CAttachment::ASH_CAttachment()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
}



void ASH_CAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = SH_CHelpers::GetComponent<USH_CStateComponent>(OwnerCharacter);
	Status = SH_CHelpers::GetComponent<USH_CStatusComponent>(OwnerCharacter);

	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* component : ShapeComponents)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ASH_CAttachment::OnComponentBeginOverlap);
		component->OnComponentEndOverlap.AddDynamic(this, &ASH_CAttachment::OnComponentEndOverlap);
	}

	Super::BeginPlay();
}

void ASH_CAttachment::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor); // 캐릭터와 같으면 무시 (적이 아니라면)
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass()); // 같은 적 무시
	
	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void ASH_CAttachment::OnComponentEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void ASH_CAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ASH_CAttachment::OnCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASH_CAttachment::OffCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}