// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ════════════════════════════════════════════════════════════════════
// 주(Primary) 게임 모듈 "ModuleAndPlugin"의 빌드 규칙입니다.
// 이 프로젝트의 캐릭터/게임모드 등 게임플레이 핵심 클래스들이 이 모듈에
// 속해 있습니다.
// ════════════════════════════════════════════════════════════════════
public class ModuleAndPlugin : ModuleRules
{
	public ModuleAndPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Third Person 템플릿 기본 의존성(Core/CoreUObject/Engine/InputCore/
		// EnhancedInput)에 더해, 우리가 새로 만든 "Test" 모듈을 추가했습니다.
		//
		// ★ 핵심 포인트 ★
		// ModuleAndPluginCharacter.cpp에서 "TestActor.h"를 include 하고
		// ATestActor를 SpawnActor로 생성하려면, 이렇게 "Test"를 의존성
		// 목록에 추가해야만 컴파일/링크가 가능합니다. 이 한 줄이 빠지면
		// "TestActor.h 파일을 찾을 수 없다(Cannot open include file)"는
		// 에러가 발생합니다.
		//
		// Public으로 넣은 이유: ModuleAndPluginCharacter.h(헤더)에서도
		// ATestActor를 전방 선언(forward declaration)하여 사용하므로,
		// 헤더 레벨에서 의존하는 모듈은 Private이 아닌 Public Dependency로
		// 등록하는 것이 맞습니다.
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Test", });
	}
}
