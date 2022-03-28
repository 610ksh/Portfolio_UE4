#include "Release/CGameMode.h"
#include "Release/Global.h"

ACGameMode::ACGameMode()
{
	Helpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/SungHoon/Projects/Characters/BP_CCountess.BP_CCountess_C'");
}