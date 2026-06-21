// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleAndPluginGameMode.h"
#include "ModuleAndPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

AModuleAndPluginGameMode::AModuleAndPluginGameMode()
{
	// 기본 Pawn 클래스를 블루프린트(BP_ThirdPersonCharacter)로 지정.
	// C++이 아닌 블루프린트 경로를 참조하므로 ConstructorHelpers를 사용합니다.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
