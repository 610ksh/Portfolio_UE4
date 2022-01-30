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
	CheckNull(MeshComp); // �޽� ����
	CheckNull(MeshComp->GetOwner()); // ĳ���� ����(Actor)

	ASH_CActionPlayer* player = Cast< ASH_CActionPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Roll();
}
