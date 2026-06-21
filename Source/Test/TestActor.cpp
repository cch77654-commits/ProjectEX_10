#include "TestActor.h"
#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	// 이 액터는 매 프레임 갱신(Tick)될 필요가 없으므로 비활성화하여
	// 불필요한 성능 비용을 줄입니다.
	PrimaryActorTick.bCanEverTick = false;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	// ── 모듈 동작 확인용 로그 ─────────────────────────────────────
	// Test 모듈이 정상적으로 컴파일/로드되었고, 이 액터가 실제로
	// 게임 월드에 스폰되어 BeginPlay까지 호출되었음을 출력 로그(Output Log)에
	// 기록합니다. 빌드/모듈 등록에 문제가 있었다면 이 로그 자체가
	// 출력되지 않거나, 애초에 컴파일이 실패합니다.
	UE_LOG(LogTemp, Warning, TEXT("[Test Module] TestActor::BeginPlay() 호출됨"));

	// ── 화면에 직접 보이는 디버그 메시지 ──────────────────────────
	// GEngine->AddOnScreenDebugMessage는 플레이 화면 좌상단에 일정 시간
	// 동안 텍스트를 띄워주는 함수입니다. 로그 파일을 따로 열어보지 않아도
	// "모듈이 살아있다"는 것을 즉시 눈으로 확인할 수 있어 테스트에 유용합니다.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,            // 메시지 고유 Key (-1이면 매번 새 줄에 추가)
			5.f,           // 화면에 표시되는 시간(초)
			FColor::Green, // 메시지 색상
			TEXT("Test 모듈의 TestActor가 정상적으로 스폰/실행되었습니다!")
		);
	}
}
