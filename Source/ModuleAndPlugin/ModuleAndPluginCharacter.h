// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ModuleAndPluginCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
// ATestActor는 "Test" 모듈에 정의된 클래스입니다. 여기서는 헤더 안에서
// 포인터만 사용할 것이므로(멤버 변수 등으로 선언 X, 함수 시그니처에도 X),
// 전체 정의를 #include 하지 않고 "전방 선언(forward declaration)"만으로
// 충분합니다. 실제 클래스 정의는 .cpp 파일에서 "TestActor.h"를 include해
// 가져옵니다. 이렇게 하면 헤더 파일의 include 양이 줄어 컴파일이 빨라집니다.
class ATestActor;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AModuleAndPluginCharacter : public ACharacter
{
	GENERATED_BODY()

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AModuleAndPluginCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	// ── 모듈 간 상호작용 확인용 ────────────────────────────────────
	// 주 게임 모듈(ModuleAndPlugin)이 Test 모듈의 클래스(ATestActor)를
	// 실제로 사용할 수 있는지 확인하기 위해 BeginPlay를 오버라이드합니다.
	// 구현은 .cpp에서 ATestActor를 스폰하는 코드로 되어 있습니다.
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
