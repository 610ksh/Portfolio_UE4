#include "Release/Actions/CActionData.h"
#include "Release/Actions/CEquipment.h"
#include "Release/Global.h"

#include "GameFramework/Character.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		UGameplayStatics::FinishSpawningActor(Equipment, transform);
	}
}