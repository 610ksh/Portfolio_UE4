#include "SH/Lecture2/SH_CActionGameMode.h"
#include "SH/SH_Global.h"


ASH_CActionGameMode::ASH_CActionGameMode()
{
	SH_CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/SungHoon/Lectures/ActionRPG/Character/SH_BP_CActionPlayer.SH_BP_CActionPlayer_C'");
	SH_CHelpers::GetClass<AHUD>(&HUDClass, "Blueprint'/Game/SungHoon/Lectures/ActionRPG/BP/SH_BP_CHUD.SH_BP_CHUD_C'");

	//DefaultPawnClass = ASH_CActionPlayer2::StaticClass();
}