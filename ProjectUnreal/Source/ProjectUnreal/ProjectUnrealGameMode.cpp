// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectUnrealGameMode.h"
#include "ProjectUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectUnrealGameMode::AProjectUnrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
