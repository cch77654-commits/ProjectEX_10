#include "Test.h"
#include "Modules/ModuleManager.h"

// ════════════════════════════════════════════════════════════════════
// [모듈 매크로 IMPLEMENT_MODULE 이란?]
// UE의 모든 모듈(.dll)은 엔진이 "이 모듈이 어디서 시작하고 끝나는지"를
// 알 수 있도록 모듈 진입점을 등록해야 합니다. 그 등록을 해주는 매크로가
// IMPLEMENT_MODULE 입니다. 이 매크로가 없으면 빌드는 되더라도
// 엔진이 이 모듈을 정식 모듈로 인식하지 못해 링크 에러가 납니다.
//
// IMPLEMENT_MODULE(구현클래스, 모듈이름)
//   - 구현클래스 : IModuleInterface를 상속해서 StartupModule()/
//                  ShutdownModule()을 직접 구현한 클래스.
//                  (Temporary 플러그인의 FTemporaryModule이 그 예시)
//   - 모듈이름   : Build.cs의 클래스 이름과 동일해야 함 ("Test")
//
// 지금 Test 모듈은 "모듈이 로드/언로드될 때 특별히 할 일이 없는,
// 단순히 클래스/액터들을 담아두는 일반(Default) 모듈"이기 때문에,
// 직접 클래스를 만들지 않고 엔진이 기본 제공하는 FDefaultModuleImpl을
// 그대로 사용합니다. (Startup/Shutdown에서 아무 일도 하지 않는 빈 구현체)
// ════════════════════════════════════════════════════════════════════
IMPLEMENT_MODULE(FDefaultModuleImpl, Test);
