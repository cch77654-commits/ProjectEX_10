// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleAndPluginCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
// ════════════════════════════════════════════════════════════════════
// ★ 모듈 간 참조(Cross-Module Reference)의 핵심 ★
// 주 게임 모듈(ModuleAndPlugin)에서 다른 모듈(Test)의 클래스를 사용하려면
// 그 클래스의 헤더를 include하면 됩니다. 단, 이게 가능하려면 사전 조건이
// 두 가지 필요합니다.
//   1) ModuleAndPlugin.Build.cs의 PublicDependencyModuleNames에 "Test"가
//      등록되어 있어야 함 (그래야 컴파일러가 Test 모듈의 include 경로와
//      라이브러리를 알 수 있음)
//   2) ATestActor 클래스가 TEST_API 매크로로 선언되어 있어야 함 (그래야
//      모듈 경계를 넘어 심볼을 가져올 수 있음 - dllimport)
// 이 두 조건이 갖춰진 상태에서야 아래 include가 정상 동작합니다.
// ════════════════════════════════════════════════════════════════════
#include "Test/TestActor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);



AModuleAndPluginCharacter::AModuleAndPluginCharacter()
{
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

}

//////////////////////////////////////////////////////////////////////////
// Input

// ════════════════════════════════════════════════════════════════════
// [모듈 간 상호작용 구현]
// 캐릭터가 게임에 스폰되어 플레이가 시작되면, Test 모듈에 정의된
// ATestActor를 캐릭터 바로 앞에 하나 스폰합니다.
//
// 이 함수가 컴파일·실행에 성공하고, 실제로 화면에 TestActor의
// 초록색 메시지("Test 모듈의 TestActor가 정상적으로 스폰/실행되었습니다!")가
// 뜬다면 → 주 모듈(ModuleAndPlugin)과 Test 모듈 사이의 의존성 설정,
// .uproject 모듈 등록, Target.cs 설정이 전부 올바르게 연결되었다는 뜻입니다.
// ════════════════════════════════════════════════════════════════════
void AModuleAndPluginCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200.f;
	const FRotator SpawnRotation = GetActorRotation();

	if (UWorld* World = GetWorld())
	{
		// SpawnActor<T>는 템플릿 함수로, Test 모듈에 정의된 ATestActor를
		// 마치 같은 모듈 안의 클래스처럼 자연스럽게 생성할 수 있습니다.
		// 이것이 가능한 이유는 위에서 include한 "TestActor.h" 덕분입니다.
		World->SpawnActor<ATestActor>(ATestActor::StaticClass(), SpawnLocation, SpawnRotation);
	}
}

void AModuleAndPluginCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AModuleAndPluginCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AModuleAndPluginCharacter::Move);

		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AModuleAndPluginCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AModuleAndPluginCharacter::Move(const FInputActionValue& Value)
{
	
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AModuleAndPluginCharacter::Look(const FInputActionValue& Value)
{
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
