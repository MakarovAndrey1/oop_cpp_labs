cmake_minimum_required(VERSION 3.10)
project(cpplab4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

# Основная программа
add_executable(cpplab4
    src/Point.cpp
    src/Figure.cpp
    src/Trapezoid.cpp
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Array.cpp
)

target_include_directories(cpplab4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(tests04
    test/tests04.cpp
    src/Point.cpp
    src/Figure.cpp
    src/Trapezoid.cpp
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Array.cpp
)

target_include_directories(tests04 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests04 GTest::gtest_main)

add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp)

include(GoogleTest)
gtest_discover_tests(tests04)

# Добавляем тесты в CTest
add_test(NAME FiguresTests COMMAND tests04)