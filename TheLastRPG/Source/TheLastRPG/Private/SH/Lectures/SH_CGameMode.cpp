#include "SH/Lectures/SH_CGameMode.h"
#include "SH/Lectures/PlayerCharacter.h"
#include "SH/SH_Global.h"

ASH_CGameMode::ASH_CGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	
	/*ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/SungHoon/Blueprints/BP_SH_Player.BP_SH_Player_C'");
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;*/

	FString url = "Blueprint'/Game/SungHoon/Lectures/GunShooting/Character/SH_BP_CPlayer.SH_BP_CPlayer_C'"; // _C¡÷¿«
	SH_CHelpers::GetClass<APawn>(&DefaultPawnClass, url);
}