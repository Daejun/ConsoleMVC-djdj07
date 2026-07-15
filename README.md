# MVC 스켈레톤 (C++ / GoogleTest)

C++17 기반 MVC 패턴 스켈레톤 프로젝트. 데이터베이스 없이 인메모리 더미 데이터를 사용하며, View는 콘솔 입출력으로 구성한다.

## 프로젝트 구조

```
mvc/
├── CMakeLists.txt              # 최상위 빌드 설정 (C++17, gtest FetchContent)
├── src/
│   ├── model/
│   │   ├── Item.h/.cpp             # 도메인 엔티티 (id, name, value)
│   │   └── ItemRepository.h/.cpp   # 인메모리 저장소 (vector 기반 더미 데이터 CRUD)
│   ├── view/
│   │   └── ConsoleView.h/.cpp      # 콘솔 출력 전담 (목록/상세/에러 메시지 포맷팅)
│   ├── controller/
│   │   └── ItemController.h/.cpp   # Model↔View 중개, 사용자 입력 처리 로직
│   └── main.cpp                    # 진입점: 메뉴 루프 (조회/추가/삭제 등)
├── tests/
│   ├── CMakeLists.txt
│   ├── ItemRepositoryTest.cpp   # Model 단위 테스트
│   ├── ItemControllerTest.cpp   # Controller 단위 테스트 (View는 mock/stub)
│   └── ConsoleViewTest.cpp      # 출력 포맷 테스트 (stdout 캡처)
└── .gitignore                   # build/ 등 제외
```

## 설계 방향

- **Model**: `Item` 엔티티 + `ItemRepository`가 `std::vector<Item>`으로 더미 데이터를 관리(add/remove/find/list). DB 없이 순수 메모리.
- **View**: 콘솔 입출력만 담당. 데이터 가공 로직 없이 문자열 포맷팅/출력만 수행해 stdout 캡처 테스트가 쉽도록 분리.
- **Controller**: View의 입력을 받아 Model을 호출하고 결과를 View에 전달. 실제 비즈니스 로직 위치.
- **테스트**: gtest는 CMake `FetchContent`로 받아오고, Model/Controller는 직접 테스트, View는 인터페이스(IView)로 분리해 Controller 테스트 시 mock 가능하도록 구성.
- **빌드**: CMake `add_subdirectory(tests)` + `enable_testing()` + `ctest`로 실행.

## 진행 순서 (TDD)

1. CMakeLists.txt + gtest 연동 스켈레톤 작성 (빈 테스트 하나로 빌드 확인)
2. Model(`Item`, `ItemRepository`) 테스트 먼저 작성 → 구현
3. Controller 테스트(View는 인터페이스로 stub) → 구현
4. ConsoleView 구현 (출력 포맷 테스트 포함)
5. main.cpp에서 메뉴 루프로 전체 연결
6. `ctest`로 전체 테스트 실행 확인

## 상태

TDD 진행 순서 1~6단계(빌드 스켈레톤 → Model → Controller → ConsoleView → main.cpp → 전체 테스트 통과) 구현 완료. `ctest`로 전체 테스트 스위트(20개) 통과 확인됨.
