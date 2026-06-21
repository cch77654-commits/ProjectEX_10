#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

// ════════════════════════════════════════════════════════════════════
// [IModuleInterface를 직접 구현하는 이유]
// Test 모듈은 FDefaultModuleImpl(엔진이 제공하는 빈 구현체)을 그대로
// 썼지만, 이 Temporary 플러그인은 "모듈이 로드/언로드되는 시점에 직접
// 어떤 동작을 하고 싶을 때" 쓰는 정석적인 방법을 보여줍니다.
//
// IModuleInterface를 상속받아 StartupModule()/ShutdownModule()을
// override하면, 플러그인이 활성화되거나 비활성화될 때 원하는 초기화/
// 정리(cleanup) 코드를 직접 실행시킬 수 있습니다.
// (예: 커스텀 에디터 메뉴 등록/해제, 전역 리소스 로드/언로드 등)
// ════════════════════════════════════════════════════════════════════
class FTemporaryModule : public IModuleInterface
{
public:
	/** IModuleInterface 구현 */

	// 이 모듈(플러그인)이 메모리에 로드될 때 한 번 호출됩니다.
	// .uproject의 Plugins 항목에서 "Enabled": true 로 설정되어 있고,
	// LoadingPhase 시점이 되면 엔진이 자동으로 이 함수를 호출합니다.
	virtual void StartupModule() override;

	// 이 모듈(플러그인)이 언로드되거나, 에디터/게임이 종료될 때 호출됩니다.
	// StartupModule에서 할당한 리소스가 있다면 여기서 해제해야 합니다.
	virtual void ShutdownModule() override;
};
