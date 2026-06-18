#include "Test.h"
#include "Modules/ModuleManager.h"

// 별도의 StartupModule/ShutdownModule 로직이 필요 없는 "일반 모듈"이므로
// FDefaultModuleImpl을 사용해 매크로만으로 모듈을 구현합니다.
IMPLEMENT_MODULE(FDefaultModuleImpl, Test);
