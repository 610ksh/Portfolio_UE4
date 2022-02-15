#include "SH/Lecture2/Widgets/SH_CUserWidget_ActionItem.h"
#include "SH/Lecture2/Widgets/SH_CUserWidget_ActionList.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"

#include "SH/SH_Global.h"


void USH_CUserWidget_ActionItem::Click()
{
	GetActionList()->Clicked(GetName());
}

void USH_CUserWidget_ActionItem::Hover()
{
	GetActionList()->Hovered(GetName());
}

void USH_CUserWidget_ActionItem::Unhover()
{
	GetActionList()->Unhovered(GetName());
}

USH_CUserWidget_ActionList * USH_CUserWidget_ActionItem::GetActionList()
{
	ASH_CActionPlayer* player = Cast<ASH_CActionPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	return player->GetActionList();
}
