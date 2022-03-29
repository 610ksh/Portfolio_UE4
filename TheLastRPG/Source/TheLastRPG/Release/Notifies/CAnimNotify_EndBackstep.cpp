#include "Release/Notifies/CAnimNotify_EndBackstep.h"
#include "Release/Characters/ICharacter.h"
#include "Release/Global.h"

FString UCAnimNotify_EndBackstep::GetNotifyName_Implementation() const
{
	return "Backstep";
}

void UCAnimNotify_EndBackstep::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IICharacter* player = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Backstep();
}