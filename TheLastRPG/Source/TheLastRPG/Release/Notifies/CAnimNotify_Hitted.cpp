#include "Release/Notifies/CAnimNotify_Hitted.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Global.h"
#include "GameFramework/Character.h"

FString UCAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void UCAnimNotify_Hitted::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);

	UCStateComponent* state = Helpers::GetComponent<UCStateComponent>(character);
	CheckNull(state);

	state->SetIdleMode();
}