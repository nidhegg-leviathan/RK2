cmake_minimum_required(VERSION 3.4)
project(rk2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)
include(CPack.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/code)

if(BUILD_TESTS)
  add_compile_options(--coverage)
endif()

add_library(code STATIC ${CMAKE_CURRENT_SOURCE_DIR}/code/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/code/proxy.cpp ${CMAKE_CURRENT_SOURCE_DIR}/code/database.cpp)
target_include_directories(code PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
target_link_libraries(code gcov)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB CODE_TEST_SOURCES tests/*.cpp)
  add_executable(check ${CODE_TEST_SOURCES})
  target_link_libraries(check code gtest_main gmock_main)
  add_test(NAME check COMMAND check)
endif()
include(CPackConfig.cmake)