// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleAndPlugin.h"
#include "Modules/ModuleManager.h"

// ════════════════════════════════════════════════════════════════════
// [IMPLEMENT_PRIMARY_GAME_MODULE 이란?]
// Test 모듈에서 본 IMPLEMENT_MODULE과 비슷하지만, "이 프로젝트의 주(메인)
// 게임 모듈"임을 표시하는 전용 매크로입니다. 프로젝트당 단 하나의 모듈만
// 이 매크로를 사용해야 합니다(나머지 추가 모듈들은 IMPLEMENT_MODULE 사용).
//
// IMPLEMENT_PRIMARY_GAME_MODULE(구현클래스, 모듈이름, "게임이름")
//   - 세 번째 인자 "ModuleAndPlugin"은 .uproject 파일 이름과 일치해야 하며,
//     패키징 시 실행 파일 이름 등에 사용됩니다.
//
// Test 모듈과 마찬가지로 별도 Startup/Shutdown 로직이 필요 없으므로
// FDefaultGameModuleImpl(엔진이 기본 제공하는 빈 구현체)을 사용합니다.
// ════════════════════════════════════════════════════════════════════
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ModuleAndPlugin, "ModuleAndPlugin" );
