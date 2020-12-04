cmake_minimum_required(VERSION 3.19)

project(SampleProject)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

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
    gtest
)

add_executable(sample_project_test ${CMAKE_CURRENT_SOURCE_DIR}/C/main_test.cpp)
target_include_directories(sample_project_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_link_libraries(sample_project_test gtest gtest_main B)
add_test(NAME sample_project_test COMMAND sample_project_test)
