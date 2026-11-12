# GI Engine

완성하지 못했던 GI Engine을 다시 만들며 WinAPI, DirectX, 게임 엔진 구조를
차근차근 학습하는 C++ 프로젝트입니다. 최종적으로 언리얼 엔진의 구조와
명명 방식에 자연스럽게 익숙해지는 것을 목표로 합니다.

학습 내용과 복습 과제는 [`docs/LearningLog.md`](docs/LearningLog.md)에 계속 기록합니다.

현재 예제에는 다음 흐름만 들어 있습니다.

- 윈도우 클래스 등록
- 기본 창 생성
- 메시지 루프 실행
- `WM_PAINT`에서 문자열 출력
- `WM_DESTROY`에서 프로그램 종료

## 지금 수정할 파일

처음에는 `src/Game.cpp`만 수정합니다. 함수와 타입 이름은 앞으로 볼
언리얼 엔진 C++ 명명 방식에 익숙해지도록 맞췄습니다.

- `BeginPlay`: 게임 시작 시 한 번 실행
- `Tick(float DeltaTime)`: 매 프레임 게임 상태 갱신
- `DrawHUD`: 매 프레임 화면 그리기
- `FColor`: 구조체 이름 앞의 `F` 접두사
- `EKey`: 열거형 이름 앞의 `E` 접두사
- `bIsRunning`: bool 변수의 `b` 접두사

`main.cpp`와 `GameAPI.cpp`는 기반 코드입니다. 게임을 먼저 만들어 본 뒤
입력, 게임 루프, 시간, WinAPI, 렌더링 순서로 분석하고 직접 교체합니다.

## Visual Studio 2026에서 빌드

1. Visual Studio Installer에서 **C++를 사용한 데스크톱 개발**을 설치합니다.
2. `GI-Engine.sln`을 엽니다.
3. 상단 구성을 `Debug`, 플랫폼을 `x64`로 선택합니다.
4. `F5` 또는 `Ctrl+F5`로 실행합니다.

## 명령줄에서 빌드

Visual Studio의 **Developer PowerShell**에서 실행합니다.

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\GI-Engine.exe
```

Ninja 같은 단일 구성 생성기를 쓰는 경우 실행 파일은 보통 `build` 폴더 바로 아래에 생성됩니다.

## 다음 연습 아이디어

1. `WM_LBUTTONDOWN`을 처리해 클릭 좌표를 표시합니다.
2. `CreateWindowW`로 버튼을 추가합니다.
3. `WM_COMMAND`에서 버튼 클릭을 처리합니다.
4. 메뉴와 대화상자 리소스를 추가합니다.
