// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTestTestGameMode.h"
#include "TestTestTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestTestTestGameMode::ATestTestTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
