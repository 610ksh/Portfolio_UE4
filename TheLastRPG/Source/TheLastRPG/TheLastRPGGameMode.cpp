// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLastRPGGameMode.h"
#include "TheLastRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "YH/Global_YH.h"

ATheLastRPGGameMode::ATheLastRPGGameMode()
{

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/StarterPack/ThirdPerson/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
