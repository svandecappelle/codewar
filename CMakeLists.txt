cmake_minimum_required(VERSION 2.6)
project(CODE_WAR)

find_package (PkgConfig REQUIRED)

add_subdirectory(src)
add_subdirectory(src/core) 

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
