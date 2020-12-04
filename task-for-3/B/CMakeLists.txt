add_library(B SHARED lib.cpp)

target_include_directories(B INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
