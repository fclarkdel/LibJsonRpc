cmake_minimum_required(VERSION 3.25)

project(LibJsonRpc)

set(
    CMAKE_CXX_STANDARD
    20
)
add_subdirectory(Source)

# Library implementors target this.
add_library(
    LibJsonRpc
    INTERFACE
)
target_link_libraries(
    LibJsonRpc
    INTERFACE
    LibJsonRpc_Source
)
target_include_directories(
    LibJsonRpc
    INTERFACE
    Source
)