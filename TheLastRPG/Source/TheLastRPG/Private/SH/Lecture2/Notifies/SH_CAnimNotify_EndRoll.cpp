#include "SH/Lecture2/Notifies/SH_CAnimNotify_EndRoll.h"
#include "SH/SH_Global.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"

FString USH_CAnimNotify_EndRoll::GetNotifyName_Implementation() const
{
	return "Roll";
}

void USH_CAnimNotify_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull_SH(MeshComp); // 메시 유무
	CheckNull_SH(MeshComp->GetOwner()); // 캐릭터 유무(Actor)

	ASH_CActionPlayer* player = Cast< ASH_CActionPlayer>(MeshComp->GetOwner());
	CheckNull_SH(player);

	player->End_Roll();
}
