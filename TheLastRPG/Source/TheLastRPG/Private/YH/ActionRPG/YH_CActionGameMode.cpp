
#include "YH/ActionRPG/YH_CActionGameMode.h"
#include "YH/Global_YH.h"

AYH_CActionGameMode::AYH_CActionGameMode()
{
	CHelpers_YH::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/YongHwan/YongHwan_RPG/Characters/YH_BP_CActionPlayer.YH_BP_CActionPlayer_C'");
	//CHelpers_YH::GetClass<AHUD>(&HUDClass, "Blueprint'/Game/SungHoon/Lectures/ActionRPG/BP/SH_BP_CHUD.SH_BP_CHUD_C'");
	
	
}