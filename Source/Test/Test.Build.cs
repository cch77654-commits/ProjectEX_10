using UnrealBuildTool;

// ════════════════════════════════════════════════════════════════════
// [Test.Build.cs 란?]
// "Test"라는 모듈을 어떻게 컴파일할지 정의하는 빌드 규칙 파일입니다.
// UE의 모든 모듈은 폴더 안에 "모듈이름.Build.cs" 파일이 반드시 있어야 하며,
// UnrealBuildTool(UBT)이 이 파일을 읽어서 컴파일 옵션과 의존성을 결정합니다.
//
// 클래스 이름(Test)은 폴더 이름·파일 이름과 반드시 동일해야 합니다.
// ════════════════════════════════════════════════════════════════════
public class Test : ModuleRules
{
	public Test(ReadOnlyTargetRules Target) : base(Target)
	{
		// PCH(Precompiled Header) 사용 방식 - 컴파일 속도 최적화 옵션
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// ── PublicDependencyModuleNames (Public 의존성) ──────────────
		// 이 모듈의 "헤더(.h) 또는 소스(.cpp)"에서 사용하는 다른 모듈 목록.
		// Public으로 등록하면, 이 Test 모듈을 가져다 쓰는 다른 모듈(예: 주 게임
		// 모듈 ModuleAndPlugin)도 자동으로 Core/Engine 등에 접근할 수 있게
		// "의존성이 전파"됩니다.
		//   - Core      : 가장 기본적인 자료형, 컨테이너, 로그 등 UE의 핵심 기능
		//   - CoreUObject : UCLASS/UPROPERTY 등 UObject 시스템(리플렉션)
		//   - Engine    : AActor, UWorld 등 게임플레이 관련 핵심 클래스
		//   - InputCore : 키보드/마우스 등 입력 관련 기본 타입
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore"
		});

		// ── PrivateDependencyModuleNames (Private 의존성) ────────────
		// 이 모듈의 "소스(.cpp) 내부 구현에서만" 사용하고, 헤더에는 노출하지
		// 않는 모듈 목록입니다. Private으로 등록하면 의존성이 외부로 전파되지
		// 않으므로, 불필요한 결합(coupling)을 줄이고 컴파일 속도도 빨라집니다.
		// 지금은 Test 모듈 구현이 단순해서 비어 있지만, 예를 들어
		// "Slate"(UI), "UMG" 등을 cpp 내부에서만 쓴다면 여기에 추가합니다.
		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});
	}
}
