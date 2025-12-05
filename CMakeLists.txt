cmake_minimum_required(VERSION 3.31.6)
project(awesome-algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE ALL_SOURCES
        CONFIGURE_DEPENDS
        "data_structure/*.hpp"
        "graph/*.hpp"
        "math/*.hpp"
        "misc/*.hpp"
        "string/*.hpp"
)

add_library(algo INTERFACE)

target_sources(algo INTERFACE
        ${ALL_SOURCES}
)

target_include_directories(algo INTERFACE
        ${CMAKE_SOURCE_DIR}
)


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()


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
