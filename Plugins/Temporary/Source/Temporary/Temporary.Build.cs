using UnrealBuildTool;

// ════════════════════════════════════════════════════════════════════
// [플러그인 모듈의 Build.cs는 일반 모듈과 사실상 동일합니다]
// "플러그인"과 "모듈"의 차이는 코드 작성 방식이 아니라 "어디에 위치하고,
// 어떻게 패키징되는가"에 있습니다.
//   - 일반 모듈(Source/Test)  : 이 프로젝트 전용. 다른 프로젝트로 가져가려면
//                               파일을 통째로 복사해야 함.
//   - 플러그인(Plugins/Temporary) : .uplugin 메타데이터를 포함한 독립
//     단위이므로, Plugins 폴더째로 다른 프로젝트에 복사하거나 마켓플레이스에
//     공개하는 등 "재사용"이 훨씬 쉬움.
// 즉 플러그인 안에도 모듈이 1개 이상 들어있고, 그 모듈의 Build.cs가 바로 이 파일입니다.
// ════════════════════════════════════════════════════════════════════
public class Temporary : ModuleRules
{
	public Temporary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Public: 헤더(Temporary.h)에서 사용하는 최소한의 모듈만 포함
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});

		// Private: .cpp 내부 구현에서만 쓰는 모듈들.
		// 지금 당장은 Temporary.cpp가 이들을 직접 쓰진 않지만, 플러그인이
		// UI(Slate)나 UObject(CoreUObject/Engine) 기능을 추가할 것을 대비해
		// 미리 등록해 둔 상태입니다.
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore"
		});
	}
}
