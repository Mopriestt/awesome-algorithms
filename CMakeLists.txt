cmake_minimum_required(VERSION 4.2)
project(awesome-algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
# 1. 所有 .hpp 模板文件（任意子目录，但限定在几个源目录里）
#
file(GLOB_RECURSE ALL_SOURCES
        CONFIGURE_DEPENDS
        "data_structure/*.hpp"
        "graph/*.hpp"
        "math/*.hpp"
        "misc/*.hpp"
        "string/*.hpp"
)

# header-only 库：algo
add_library(algo INTERFACE)

# 为了 IDE 识别，把所有头文件挂到 algo 上
target_sources(algo INTERFACE
        ${ALL_SOURCES}
)

# 头文件根目录就是项目根
target_include_directories(algo INTERFACE
        ${CMAKE_SOURCE_DIR}
)

#
# 2. 引入 GoogleTest（FetchContent）
#
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

#
# 3. 所有 .cpp 都是测试文件，同样限定在源代码子目录里
#
file(GLOB_RECURSE TEST_SOURCES
        CONFIGURE_DEPENDS
        "data_structure/*.cpp"
        "graph/*.cpp"
        "math/*.cpp"
        "misc/*.cpp"
        "string/*.cpp"
)

add_executable(algo_tests
        ${TEST_SOURCES}
)

target_include_directories(algo_tests PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(algo_tests
        PRIVATE
        algo
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(algo_tests)
