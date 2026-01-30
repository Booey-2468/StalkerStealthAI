// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyAIGameMode.h"
#include "EnemyAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnemyAIGameMode::AEnemyAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
