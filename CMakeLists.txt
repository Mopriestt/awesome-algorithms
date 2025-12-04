cmake_minimum_required(VERSION 4.2)
project(awesome-algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE ALL_SOURCES
        "data_structure/*.cpp"
        "graph/*.cpp"
        "math/*.cpp"
        "misc/*.cpp"
        "string/*.cpp"
        "string/*.hpp"
)

foreach(SOURCE_FILE ${ALL_SOURCES})
    get_filename_component(SOURCE_NAME ${SOURCE_FILE} NAME_WE)
    get_filename_component(SOURCE_DIR ${SOURCE_FILE} DIRECTORY)

    file(RELATIVE_PATH RELATIVE_PATH ${CMAKE_SOURCE_DIR} ${SOURCE_DIR})

    string(REPLACE "/" "_" EXEC_NAME "${RELATIVE_PATH}_${SOURCE_NAME}")

    add_executable(${EXEC_NAME} ${SOURCE_FILE})

    set_target_properties(${EXEC_NAME} PROPERTIES
            OUTPUT_NAME ${EXEC_NAME}g
    )
endforeach()