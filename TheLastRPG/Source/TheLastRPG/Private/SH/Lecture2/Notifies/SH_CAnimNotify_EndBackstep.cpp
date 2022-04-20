#include "SH/Lecture2/Notifies/SH_CAnimNotify_EndBackstep.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/SH_Global.h"

FString USH_CAnimNotify_EndBackstep::GetNotifyName_Implementation() const
{
	return "Backstep";
}

void USH_CAnimNotify_EndBackstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	SH_CheckNull(MeshComp); // �޽� ����
	SH_CheckNull(MeshComp->GetOwner()); // ĳ���� ����(Actor)

	ASH_CActionPlayer* player = Cast<ASH_CActionPlayer>(MeshComp->GetOwner());
	SH_CheckNull(player);

	player->End_Backstep();
}