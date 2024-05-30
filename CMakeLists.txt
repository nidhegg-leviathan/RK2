cmake_minimum_required(VERSION 3.10)

project(RK2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
    code/main.cpp
    code/proxy.cpp
    code/database.cpp
)

# Добавление исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Добавление пути к заголовочным файлам
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Добавление заголовочных файлов
set(HEADERS
    code/databaseparent.h
    code/proxy.h
    code/database.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

include(CPack.cmake)
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "${CMAKE_SOURCE_DIR}")

if(BUILD_TESTS)
  add_compile_options(--coverage)
endif()


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB CODE_TEST_SOURCES tests/*.cpp)
  add_executable(check ${CODE_TEST_SOURCES})
  target_link_libraries(check gtest_main gmock_main)
  add_test(NAME check COMMAND check)
endif()
