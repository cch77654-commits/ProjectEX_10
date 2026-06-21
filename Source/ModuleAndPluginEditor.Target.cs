using UnrealBuildTool;
using System.Collections.Generic;

// ════════════════════════════════════════════════════════════════════
// [Editor.Target.cs 란?]
// 위의 ModuleAndPlugin.Target.cs와 거의 동일하지만, Type이 Editor로 되어 있어
// "언리얼 에디터 자체를 실행할 때" 사용되는 빌드 설정입니다.
// 에디터에서 플레이(Play In Editor)를 누르거나, 코드를 컴파일(F7/Build)할 때
// 실제로는 대부분 이 Editor Target이 사용됩니다.
//
// 게임 Target과 Editor Target 양쪽 모두에 "Test"를 추가해줘야,
// 에디터에서도, 패키징된 게임에서도 Test 모듈이 정상적으로 빌드/로드됩니다.
// ════════════════════════════════════════════════════════════════════
public class ModuleAndPluginEditorTarget : TargetRules
{
	public ModuleAndPluginEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		// 에디터 빌드에도 동일하게 "Test" 모듈을 포함시킴
		ExtraModuleNames.AddRange(new string[] { "ModuleAndPlugin", "Test" });
	}
}
