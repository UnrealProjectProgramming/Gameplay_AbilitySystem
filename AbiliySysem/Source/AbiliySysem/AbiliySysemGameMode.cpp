// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AbiliySysemGameMode.h"
#include "AbiliySysemHUD.h"
#include "AbiliySysemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAbiliySysemGameMode::AAbiliySysemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAbiliySysemHUD::StaticClass();
}
