cmake_minimum_required(VERSION 3.10)
project(cpplab5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Основная программа
add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp)

# Тесты
add_executable(tests05 test/tests05.cpp)

# Все целевые файлы должны видеть заголовки
target_include_directories(${CMAKE_PROJECT_NAME}_exe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tests05 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Связываем тесты с GTest
target_link_libraries(tests05 GTest::gtest_main)

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(tests05)

# Добавляем тест в CTest
add_test(NAME StackTests COMMAND tests05)