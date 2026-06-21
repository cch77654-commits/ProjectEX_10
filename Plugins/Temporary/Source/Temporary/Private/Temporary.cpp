#include "Temporary.h"

// LOCTEXT_NAMESPACE는 텍스트 현지화(다국어 지원)를 위한 매크로 영역
// 표시자입니다. 지금은 번역 텍스트를 쓰지 않지만, 에디터 UI를 추가할
// 플러그인이라면 이 네임스페이스 안에서 NSLOCTEXT/LOCTEXT를 사용합니다.
#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	// 플러그인이 로드되는 순간 한 번 실행됩니다.
	// 이 로그가 에디터 실행 시 출력 로그(Output Log)에 찍힌다면,
	// .uproject의 Plugins 목록에 Temporary가 정상적으로 활성화되어
	// 있다는 뜻입니다.
	UE_LOG(LogTemp, Log, TEXT("[Temporary Plugin] StartupModule() 호출됨 - 플러그인이 로드되었습니다."));
}

void FTemporaryModule::ShutdownModule()
{
	// 플러그인이 언로드(또는 에디터 종료)될 때 실행됩니다.
	UE_LOG(LogTemp, Log, TEXT("[Temporary Plugin] ShutdownModule() 호출됨 - 플러그인이 종료됩니다."));
}

#undef LOCTEXT_NAMESPACE

// ════════════════════════════════════════════════════════════════════
// IMPLEMENT_MODULE(FTemporaryModule, Temporary)
// Test 모듈의 IMPLEMENT_MODULE(FDefaultModuleImpl, Test)와 형태는 같지만,
// 여기서는 첫 번째 인자로 "직접 구현한" FTemporaryModule 클래스를 넘겨서
// 위의 StartupModule/ShutdownModule이 실제로 호출되도록 연결합니다.
// 이 매크로가 곧 "Temporary"라는 모듈 이름과 FTemporaryModule 구현체를
// 엔진의 모듈 매니저에 등록하는 역할을 합니다.
// ════════════════════════════════════════════════════════════════════
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
