#include "SH/Lecture2/SH_CActionGameMode.h"
//#include "SH/Lecture2/Characters/SH_CActionPlayer2.h"
#include "SH/SH_Global.h"


ASH_CActionGameMode::ASH_CActionGameMode()
{
	SH_CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/SungHoon/Lectures/ActionRPG/Character/SH_BP_CActionPlayer.SH_BP_CActionPlayer_C'");

	//DefaultPawnClass = ASH_CActionPlayer2::StaticClass();
}