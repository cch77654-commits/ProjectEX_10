# ModuleAndPlugin (ProjectEX_10)

언리얼 엔진 5(C++) 프로젝트에서 **모듈(Module)**과 **플러그인(Plugin)**을 처음부터
직접 만들어보는 실습용 프로젝트입니다. Third Person 템플릿을 기반으로,
1) 새 모듈 `Test`를 만들어 주 게임 모듈과 연결하고,
2) 새 플러그인 `Temporary`를 만들어 프로젝트에 등록하는 과정을 담고 있습니다.

---

## 1. 폴더 구조

```
ModuleAndPlugin/
├── ModuleAndPlugin.uproject       ← 프로젝트 정의 파일 (모듈/플러그인 등록)
├── Config/                        ← 엔진/게임 설정(ini)
├── Content/                       ← 블루프린트, 메시 등 콘텐츠 애셋
├── Source/                        ← C++ 소스 코드
│   ├── ModuleAndPlugin.Target.cs        ← "게임" 빌드 타겟 설정
│   ├── ModuleAndPluginEditor.Target.cs  ← "에디터" 빌드 타겟 설정
│   ├── ModuleAndPlugin/            ← 주(Primary) 게임 모듈
│   │   ├── ModuleAndPlugin.Build.cs
│   │   ├── ModuleAndPlugin.h / .cpp
│   │   ├── ModuleAndPluginCharacter.h / .cpp
│   │   └── ModuleAndPluginGameMode.h / .cpp
│   └── Test/                       ← 새로 추가한 모듈
│       ├── Test.Build.cs
│       ├── Test.h / .cpp
│       └── TestActor.h / .cpp
└── Plugins/
    └── Temporary/                  ← 새로 추가한 플러그인
        ├── Temporary.uplugin
        ├── Content/
        └── Source/Temporary/
            ├── Temporary.Build.cs
            └── Public/Temporary.h, Private/Temporary.cpp
```

---

## 2. 모듈(Module)이란?

언리얼 엔진의 프로젝트는 하나의 거대한 코드 덩어리가 아니라, **여러 개의
모듈(.dll 단위)**로 나뉘어 컴파일됩니다. 새 프로젝트를 만들면 기본적으로
프로젝트 이름과 동일한 "주 모듈" 하나(`ModuleAndPlugin`)만 존재하는데,
이 프로젝트에서는 거기에 더해 **`Test`라는 모듈을 직접 추가**했습니다.

### 2-1. 모듈을 구성하는 3가지 필수 파일

| 파일 | 역할 |
|---|---|
| `Test.Build.cs` | 이 모듈을 **어떻게 컴파일**할지(어떤 다른 모듈에 의존하는지) 정의 |
| `Test.h` | 모듈의 진입점 헤더 (관례상 모듈 이름과 동일) |
| `Test.cpp` | `IMPLEMENT_MODULE` 매크로로 모듈을 엔진에 등록하는 구현부 |

세 파일 모두 코드 안에 한글 주석으로 자세히 설명을 달아두었으니, 직접
열어서 읽어보시는 걸 추천합니다.

### 2-2. Public Dependency vs Private Dependency

`Build.cs` 파일에서 가장 중요한 개념입니다.

- **Public Dependency** (`PublicDependencyModuleNames`)
  헤더(`.h`)와 소스(`.cpp`) **양쪽 모두**에서 사용하는 모듈. Public으로
  등록하면 이 모듈을 가져다 쓰는 **다른 모듈에까지 의존성이 전파**됩니다.
- **Private Dependency** (`PrivateDependencyModuleNames`)
  소스(`.cpp`) 파일 **내부 구현에서만** 사용하는 모듈. 외부로 전파되지
  않아 모듈 간 결합도를 낮추고 컴파일 속도를 높입니다.

> 예: 주 모듈(`ModuleAndPlugin`)의 캐릭터 클래스 **헤더**에서
> `class ATestActor;`로 `Test` 모듈의 클래스를 전방 선언하기 때문에,
> `ModuleAndPlugin.Build.cs`에서는 `Test`를 **Public**으로 등록했습니다.
> 만약 헤더에서는 전혀 쓰지 않고 `.cpp`에서만 썼다면 Private이 맞습니다.

### 2-3. 모듈을 "실제 빌드에 포함시키는" 3단계

모듈 폴더와 3종 파일을 만들었다고 해서 자동으로 빌드에 포함되지
**않습니다.** 아래 3곳에 추가로 등록해야 비로소 컴파일 대상이 됩니다.

1. **`Target.cs`의 `ExtraModuleNames`**
   `ModuleAndPlugin.Target.cs`와 `ModuleAndPluginEditor.Target.cs`
   양쪽 모두에 `"Test"`를 추가해야 합니다. (게임 빌드용 / 에디터 빌드용
   각각 별도 설정이기 때문)
2. **`.uproject`의 `Modules` 배열**
   ```jsonc
   {
       "Name": "Test",
       "Type": "Runtime",
       "LoadingPhase": "PreDefault"   // 주 모듈보다 먼저 로드되도록 설정
   }
   ```
   - `Type: "Runtime"` → 게임 실행 중에도 필요한 일반 모듈
   - `LoadingPhase: "PreDefault"` → 주 모듈(`Default` 단계)이 로드되기
     **이전**에 먼저 로드되도록 지정. 주 모듈이 `Test` 모듈의 클래스를
     참조하므로, `Test`가 먼저 준비되어 있어야 안전합니다.
3. **Visual Studio 프로젝트 재생성**
   위 설정을 마친 뒤 `.uproject` 우클릭 → *Generate Visual Studio
   project files* 를 실행해야 솔루션에 새 모듈이 인식됩니다.

### 2-4. 모듈 간 상호작용 (Test → ModuleAndPlugin)

`Test` 모듈에는 `ATestActor`라는 단순한 액터 클래스가 있고
(`BeginPlay()`에서 로그 + 화면 메시지 출력), 주 모듈의
`AModuleAndPluginCharacter::BeginPlay()`에서 이 액터를 `SpawnActor`로
직접 생성합니다.

```cpp
// ModuleAndPluginCharacter.cpp
#include "TestActor.h"   // 다른 모듈의 헤더를 include

void AModuleAndPluginCharacter::BeginPlay()
{
    Super::BeginPlay();
    const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200.f;
    World->SpawnActor<ATestActor>(ATestActor::StaticClass(), SpawnLocation, SpawnRotation);
}
```

이게 정상적으로 컴파일되려면:
- `Test.Build.cs`가 `Test`를 빌드에 포함되도록 설정되어 있고,
- `ModuleAndPlugin.Build.cs`의 `PublicDependencyModuleNames`에 `"Test"`가
  있어야 하며,
- `TestActor.h`의 클래스 선언에 `TEST_API` 매크로(모듈 간 심볼 공개용)가
  붙어 있어야 합니다.

**플레이 버튼을 눌렀을 때 화면에 초록색 메시지가 뜨면** → 두 모듈이
정상적으로 연결되었다는 확인입니다.

---

## 3. 플러그인(Plugin)이란?

플러그인은 "모듈을 한 단계 더 패키징한 것"이라고 이해하면 쉽습니다.
코드를 작성하는 방식(Build.cs, 모듈 인터페이스 구현)은 일반 모듈과
동일하지만, 차이는 다음과 같습니다.

| | 일반 모듈 (`Source/Test`) | 플러그인 (`Plugins/Temporary`) |
|---|---|---|
| 위치 | 프로젝트 `Source/` 폴더 안 | 프로젝트 `Plugins/` 폴더 안 |
| 재사용성 | 이 프로젝트 전용 (다른 프로젝트로 옮기려면 코드를 통째로 복사) | `Plugins/Temporary` 폴더째로 다른 프로젝트에 복사하거나 마켓플레이스에 배포 가능 |
| 메타데이터 | 없음 | `.uplugin` 파일 (버전, 설명, 포함 모듈 등 JSON 메타데이터) |
| 콘텐츠 | 프로젝트 Content와 공유 | 자체 `Content/` 폴더를 가질 수 있음 (콘텐츠 브라우저에 별도 폴더로 표시) |
| On/Off | 항상 빌드에 포함 | `.uproject`의 `Enabled` 값으로 켜고 끌 수 있음 |

### 3-1. `Temporary.uplugin` 파일

```jsonc
{
    "FileVersion": 3,
    "FriendlyName": "Temporary",          // 에디터의 플러그인 목록에 표시될 이름
    "Description": "...",                  // 플러그인 설명
    "CanContainContent": true,             // Content 폴더 사용 허용 여부
    "Modules": [
        {
            "Name": "Temporary",           // 이 플러그인이 포함하는 모듈 이름
            "Type": "Runtime",             // 게임 실행 중에도 필요
            "LoadingPhase": "Default"
        }
    ]
}
```
플러그인 하나는 내부에 **모듈을 1개 이상** 포함할 수 있습니다.
이 `Modules` 배열이 바로 "`.uproject`의 `Modules` 배열"과 똑같은
역할을 플러그인 범위 안에서 수행합니다.

### 3-2. 모듈 인터페이스를 직접 구현 (`FTemporaryModule`)

`Test` 모듈은 엔진이 기본 제공하는 `FDefaultModuleImpl`을 그대로
썼지만, `Temporary` 플러그인은 `IModuleInterface`를 **직접 상속**해서
`StartupModule()` / `ShutdownModule()`을 구현했습니다.

```cpp
// Temporary.h
class FTemporaryModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;   // 플러그인 로드 시 1회 호출
    virtual void ShutdownModule() override;   // 플러그인 언로드/종료 시 1회 호출
};
```

```cpp
// Temporary.cpp
void FTemporaryModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("[Temporary Plugin] StartupModule() 호출됨 - 플러그인이 로드되었습니다."));
}
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
```

이 방식은 "플러그인이 켜질 때 메뉴를 등록한다", "전역 리소스를
미리 로드한다" 같은 **초기화 로직이 필요한 실제 플러그인**을 만들 때
사용하는 정석적인 패턴입니다.

### 3-3. 플러그인 활성화 (`.uproject`)

```jsonc
"Plugins": [
    { "Name": "Temporary", "Enabled": true }
]
```
`Enabled: true`로 등록해야 에디터/게임 실행 시 이 플러그인이 로드됩니다.
`false`로 바꾸거나 항목을 지우면 플러그인 코드 자체는 디스크에 남아있어도
빌드/실행에서 완전히 제외됩니다.

---

## 4. 빌드 및 실행 방법

1. `ModuleAndPlugin.uproject` 우클릭 → **Generate Visual Studio project
   files** 실행 (모듈/플러그인 구조를 새로 등록했을 때 항상 다시 실행)
2. `.sln` 파일을 Visual Studio로 열고 `Development Editor` 구성으로 빌드
3. 빌드 완료 후 `.uproject`를 더블클릭해 에디터 실행
4. 에디터에서 **Play** 버튼 클릭

## 5. 정상 동작 확인 체크리스트

- [ ] 플레이 시작 직후 화면에 초록색 메시지
      `"Test 모듈의 TestActor가 정상적으로 스폰/실행되었습니다!"` 표시
      → `Test` 모듈과 주 모듈의 연결 확인
- [ ] Output Log에 `[Temporary Plugin] StartupModule() 호출됨` 로그
      → `Temporary` 플러그인이 정상적으로 로드됐는지 확인
- [ ] 콘텐츠 브라우저 우측 상단 설정(톱니바퀴) → **Show Plugin Content**
      체크 시 `Temporary Content` 폴더가 보이는지 확인

## 6. 참고: 자주 헷갈리는 용어 정리

| 용어 | 의미 |
|---|---|
| `ExtraModuleNames` | 이 빌드 타겟에 포함시킬 모듈 이름 목록 (Target.cs) |
| `PublicDependencyModuleNames` | 헤더+소스 모두에서 쓰는 의존 모듈 (의존성 전파됨) |
| `PrivateDependencyModuleNames` | 소스에서만 쓰는 의존 모듈 (의존성 전파 안 됨) |
| `LoadingPhase` | 모듈이 엔진 부팅 과정 중 **언제** 로드될지 지정 (`PreDefault`가 `Default`보다 먼저) |
| `IMPLEMENT_MODULE` | 일반 모듈을 엔진에 등록하는 매크로 |
| `IMPLEMENT_PRIMARY_GAME_MODULE` | 프로젝트의 주(메인) 모듈 1개에만 사용하는 등록 매크로 |
| `TEST_API` 같은 `OOO_API` 매크로 | 모듈 경계를 넘어 클래스를 공개(export/import)하기 위한 매크로 |
