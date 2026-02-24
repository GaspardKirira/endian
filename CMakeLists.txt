cmake_minimum_required(VERSION 3.20)
project(endian LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(endian INTERFACE)
add_library(endian::endian ALIAS endian)

target_include_directories(endian INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(endian INTERFACE /W4 /permissive-)
else()
  target_compile_options(endian INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(endian_basic_test tests/test_basic.cpp)
target_link_libraries(endian_basic_test PRIVATE endian::endian)
add_test(NAME endian.basic COMMAND endian_basic_test)
