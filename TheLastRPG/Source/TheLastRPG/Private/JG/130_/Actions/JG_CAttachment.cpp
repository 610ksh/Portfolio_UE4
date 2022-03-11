// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Actions/JG_CAttachment.h"

#include "JG/130_/Components/JG_CStateComponent.h"
#include "JG/130_/Components/JG_CStatusComponent.h"
#include "JG/JG_Global.h"
#include "GameFramework/Character.h" 
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AJG_CAttachment::AJG_CAttachment()
{


}

// Called when the game starts or when spawned
void AJG_CAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = JG_Helpers::GetComponent<UJG_CStateComponent>(OwnerCharacter);
	Status = JG_Helpers::GetComponent<UJG_CStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
	
}

void AJG_CAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}