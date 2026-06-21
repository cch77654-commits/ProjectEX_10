// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModuleAndPluginGameMode.generated.h"

// Third Person 템플릿이 기본 제공하는 게임모드 클래스.
// 플레이어가 빙의할 기본 Pawn(캐릭터) 클래스를 지정하는 역할을 합니다.
// 모듈/플러그인 실습과는 직접 관련이 없는 템플릿 기본 코드입니다.
UCLASS(minimalapi)
class AModuleAndPluginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AModuleAndPluginGameMode();
};
