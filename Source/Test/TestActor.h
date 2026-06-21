#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

// ════════════════════════════════════════════════════════════════════
// ATestActor
// Test 모듈 안에 정의된, AActor를 상속받는 가장 단순한 형태의 액터 클래스.
// "새로 만든 모듈이 실제로 정상 동작하는지"를 눈으로 확인하기 위한
// 테스트용 클래스입니다. (실제 게임 로직보다는 검증/예제 목적)
//
// TEST_API 매크로:
//   모듈마다 자동 생성되는 "OOO_API" 매크로가 있습니다(여기선 TEST_API).
//   이 매크로는 dllexport/dllimport를 자동으로 처리해 줍니다.
//     - Test 모듈 내부에서 컴파일될 때는 dllexport(외부에 공개)
//     - 다른 모듈(ModuleAndPlugin)에서 이 헤더를 include할 때는
//       dllimport(외부 모듈의 심볼을 가져다 씀)
//   이 매크로 없이 클래스를 선언하면, 다른 모듈에서 이 클래스를
//   참조할 때(예: SpawnActor<ATestActor>) 링크 에러가 발생합니다.
//   → 즉, 모듈 간에 클래스를 "공유"하려면 이 API 매크로가 필수입니다.
// ════════════════════════════════════════════════════════════════════
UCLASS()
class TEST_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	ATestActor();

protected:
	// 액터가 월드에 스폰되어 플레이가 시작될 때 한 번 호출되는 함수.
	// 여기서 "이 액터가 정상적으로 스폰/실행되었는지" 로그와 화면 메시지로
	// 확인합니다.
	virtual void BeginPlay() override;
};
