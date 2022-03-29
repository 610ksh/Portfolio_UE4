#include "Release/Notifies/CAnimNotify_EndRoll.h"
#include "Release/Characters/ICharacter.h"
#include "Release/Global.h"

FString UCAnimNotify_EndRoll::GetNotifyName_Implementation() const
{
	return "Roll";
}

void UCAnimNotify_EndRoll::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IICharacter* player = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Roll();
}
