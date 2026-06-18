#include "TestActor.h"
#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[Test Module] TestActor::BeginPlay() 호출됨"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Green,
			TEXT("Test 모듈의 TestActor가 정상적으로 스폰/실행되었습니다!")
		);
	}
}
