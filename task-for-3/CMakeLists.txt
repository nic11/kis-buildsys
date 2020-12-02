cmake_minimum_required(VERSION 3.19)

project(SampleProject)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated/A)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/index.h
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/A/preparing.py
        ${CMAKE_CURRENT_SOURCE_DIR}/A/funcs.json
        ${CMAKE_CURRENT_BINARY_DIR}/generated/A
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/A/preparing.py
)

add_subdirectory(B)

add_executable(
    sample_project
    ${CMAKE_CURRENT_BINARY_DIR}/generated/index.h
    ${CMAKE_CURRENT_SOURCE_DIR}/C/main.cpp
)

target_include_directories(
    sample_project
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_link_libraries(
    sample_project
    PRIVATE
    B
)
