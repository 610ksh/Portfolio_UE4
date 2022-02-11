// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/130_/Weapons/JG_CSword.h"
#include "JG/JG_Global.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"

AJG_CSword* AJG_CSword::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<AJG_CSword>(params);
}

// Sets default values
AJG_CSword::AJG_CSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Character2_Action/Weapons/Sword/SK_Straight_Sword.SK_Straight_Sword'");
	Mesh->SetSkeletalMesh(mesh);

	JG_Helpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/JongGyun/130_/Player/Char/Sword_Grab_Montage.Sword_Grab_Montage'");
	JG_Helpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/JongGyun/130_/Player/Char/Sword_Ungrab_Montage.Sword_Ungrab_Montage'");

}

// Called when the game starts or when spawned
void AJG_CSword::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

// Called every frame
void AJG_CSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

