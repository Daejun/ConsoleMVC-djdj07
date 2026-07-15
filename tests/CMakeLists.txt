include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(mvc_tests
  PlaceholderTest.cpp
  ItemRepositoryTest.cpp
  ${CMAKE_SOURCE_DIR}/src/model/ItemRepository.cpp
)

target_include_directories(mvc_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mvc_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(mvc_tests)
