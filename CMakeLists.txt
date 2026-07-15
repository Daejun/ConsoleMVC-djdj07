cmake_minimum_required(VERSION 3.14)
project(mvc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mvc_app
  src/main.cpp
  src/model/ItemRepository.cpp
  src/controller/ItemController.cpp
  src/view/ConsoleView.cpp
)
target_include_directories(mvc_app PRIVATE src)

enable_testing()
add_subdirectory(tests)
