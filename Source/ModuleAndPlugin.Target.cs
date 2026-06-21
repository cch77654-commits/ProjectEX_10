using UnrealBuildTool;
using System.Collections.Generic;

// ════════════════════════════════════════════════════════════════════
// [Target.cs 란?]
// "이 게임을 실행 파일(.exe)로 빌드할 때 어떤 모듈들을 묶어서 컴파일할지"를
// 정의하는 설정 파일입니다. UE 프로젝트에는 보통 2개의 Target.cs가 있습니다.
//   1) ModuleAndPlugin.Target.cs        → 실제 게임(패키징/플레이) 빌드용
//   2) ModuleAndPluginEditor.Target.cs  → 에디터에서 실행할 때 쓰는 빌드용
// ════════════════════════════════════════════════════════════════════
public class ModuleAndPluginTarget : TargetRules
{
	public ModuleAndPluginTarget(TargetInfo Target) : base(Target)
	{
		// 게임(Game) 타입 빌드임을 명시 (Editor/Client/Server 등과 구분)
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		// ── ExtraModuleNames ──────────────────────────────────────────
		// 이 빌드 타겟에 "추가로 포함시킬 모듈" 목록입니다.
		// "ModuleAndPlugin" : 프로젝트 생성 시 기본으로 만들어지는 주(Primary) 게임 모듈
		// "Test"            : 우리가 직접 새로 만든 커스텀 모듈
		//
		// 여기에 "Test"를 적어주지 않으면, Test 모듈의 Build.cs/.h/.cpp 파일이
		// 폴더에 존재하더라도 UnrealBuildTool이 컴파일 대상에서 제외해버립니다.
		// 즉, 모듈 폴더를 만드는 것과 "이 빌드에 포함시키는 것"은 별개의 작업입니다.
		ExtraModuleNames.AddRange(new string[] { "ModuleAndPlugin", "Test" });
	}
}
