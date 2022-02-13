#include "SH/Lecture2/Actions/SH_CDoAction_FireStorm.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/Components/SH_CStatusComponent.h"

#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

void ASH_CDoAction_FireStorm::BeginPlay()
{
	Super::BeginPlay();
}

void ASH_CDoAction_FireStorm::DoAction()
{
	CheckFalse(*bEquipped);
	CheckFalse(State->IsIdleMode());
	
	State->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ASH_CDoAction_FireStorm::Begin_DoAction()
{

}

void ASH_CDoAction_FireStorm::End_DoActin()
{
	State->SetIdleMode();
	Status->SetMove();
}