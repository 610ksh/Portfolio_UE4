#include "SH/Lecture2/Notifies/SH_CAnimNotify_Hitted.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

FString USH_CAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void USH_CAnimNotify_Hitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull_SH(MeshComp); // 메시 유무
	CheckNull_SH(MeshComp->GetOwner()); // 캐릭터 유무(Actor)

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull_SH(character);

	USH_CStateComponent* state = SH_CHelpers::GetComponent<USH_CStateComponent>(character);
	CheckNull_SH(state);

	state->SetIdleMode();
}

