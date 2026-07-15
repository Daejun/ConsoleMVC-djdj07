# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 프로젝트 현재 상태

이 저장소에는 현재 설계 문서(`README.md`)만 존재하며, 소스 코드/빌드 파일/테스트는 아직 작성되지 않았다. 아래 내용은 구축 예정인 목표 구조를 설명한 것이므로, 여기서 언급하는 파일이 실제로 존재하는지 먼저 확인한 뒤 작업할 것.

## 아키텍처

DB 없는 C++17 MVC 스켈레톤. Model 계층은 인메모리 더미 데이터를 보관하며, View는 GUI/웹 뷰가 아닌 콘솔 기반(stdin/stdout)이다.

- **Model** (`src/model/`): `Item` 엔티티 + `ItemRepository`가 `std::vector<Item>`으로 더미 데이터를 관리(add/remove/find/list). 영속화 없음 — 프로세스 생명주기 동안만 메모리에 존재.
- **View** (`src/view/`): `ConsoleView`는 콘솔 입출력(목록/상세/에러 메시지 포맷팅 및 출력)만 담당한다. 데이터 로직을 포함하지 않기 때문에 비즈니스 로직과 독립적으로 stdout 캡처 테스트가 가능하다. `IView` 인터페이스 뒤에 설계되어 있어 `ItemController` 테스트 시 실제 콘솔 대신 stub/mock을 사용할 수 있다.
- **Controller** (`src/controller/`): `ItemController`가 실제 비즈니스 로직이 위치하는 곳이다 — View를 통해 입력을 받아 Model을 호출하고 결과를 View에 전달한다. 대부분의 로직 변경은 이 계층을 대상으로 해야 한다.
- **진입점** (`src/main.cpp`): Model/View/Controller를 연결하고 메뉴 루프(목록/추가/삭제 등)를 실행한다.

## 빌드 시스템 (예정)

CMake 기반이며, GoogleTest는 시스템 설치 의존성이 아니라 `FetchContent`로 가져온다. 테스트는 `tests/` 아래 자체 `CMakeLists.txt`를 가지며, `add_subdirectory(tests)` + `enable_testing()`으로 추가되어 `ctest`로 실행된다.

## 개발 방식

이 프로젝트는 테스트 우선(TDD) 방식으로 구축 중이다: 각 계층마다 `src/`의 구현보다 `tests/`의 테스트를 먼저 작성한다. 빌드 순서:

1. 최상위 `CMakeLists.txt` + GoogleTest `FetchContent` 연동 — 플레이스홀더 테스트 하나로 확인.
2. Model(`Item`, `ItemRepository`) — 테스트 먼저 작성 후 구현.
3. Controller(`ItemController`) — stub `IView`를 사용한 테스트 먼저 작성 후 구현.
4. `ConsoleView` 구현 — 출력 포맷 테스트(stdout 캡처) 포함.
5. `main.cpp` 메뉴 루프로 전체 연결.
6. 전체 `ctest` 실행으로 테스트 스위트 통과 확인.
