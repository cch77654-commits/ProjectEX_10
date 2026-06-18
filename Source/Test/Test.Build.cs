using UnrealBuildTool;

public class Test : ModuleRules
{
	public Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 헤더(.h)와 소스(.cpp) 모두에서 사용하는 모듈
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore"
		});

		// 소스(.cpp) 파일에서만 사용하는 모듈 (필요 시 추가)
		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});
	}
}
